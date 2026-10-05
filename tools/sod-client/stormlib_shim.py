"""Small pympq-compatible wrapper around StormLib."""

import ctypes
import ctypes.util
import os


MPQ_CREATE_ARCHIVE_V1 = 0x00000000
MPQ_CREATE_LISTFILE = 0x00100000
MPQ_CREATE_ATTRIBUTES = 0x00200000
MPQ_FILE_COMPRESS = 0x00000200
MPQ_FILE_REPLACEEXISTING = 0x80000000
MPQ_COMPRESSION_ZLIB = 0x02

MPQ_OPEN_READ_ONLY = 0x00000100
MPQ_COMPRESSION_NEXT_SAME = 0xFFFFFFFF
SFILE_OPEN_FROM_MPQ = 0x00000000

_DWORD = ctypes.c_uint32
_HANDLE = ctypes.c_void_p
_library_name = ctypes.util.find_library("storm") or "libstorm.so"
_storm = ctypes.CDLL(_library_name, use_errno=True)

_storm.SFileOpenArchive.argtypes = [ctypes.c_char_p, _DWORD, _DWORD,
                                    ctypes.POINTER(_HANDLE)]
_storm.SFileOpenArchive.restype = ctypes.c_bool
_storm.SFileHasFile.argtypes = [_HANDLE, ctypes.c_char_p]
_storm.SFileHasFile.restype = ctypes.c_bool
_storm.SFileExtractFile.argtypes = [_HANDLE, ctypes.c_char_p, ctypes.c_char_p,
                                    _DWORD]
_storm.SFileExtractFile.restype = ctypes.c_bool
_storm.SFileCreateArchive.argtypes = [ctypes.c_char_p, _DWORD, _DWORD,
                                      ctypes.POINTER(_HANDLE)]
_storm.SFileCreateArchive.restype = ctypes.c_bool
_storm.SFileAddFileEx.argtypes = [_HANDLE, ctypes.c_char_p, ctypes.c_char_p,
                                  _DWORD, _DWORD, _DWORD]
_storm.SFileAddFileEx.restype = ctypes.c_bool
_storm.SFileCloseArchive.argtypes = [_HANDLE]
_storm.SFileCloseArchive.restype = ctypes.c_bool

if hasattr(_storm, "GetLastError"):
    _storm.GetLastError.argtypes = []
    _storm.GetLastError.restype = _DWORD


def _text(value):
    return os.fsencode(value)


def _flags(values):
    result = 0
    for value in values:
        result |= int(value)
    return result


def _raise_storm_error(operation, path=None):
    if hasattr(_storm, "GetLastError"):
        code = int(_storm.GetLastError())
    else:
        code = ctypes.get_errno()
    message = "StormLib %s failed (error %d)" % (operation, code)
    raise OSError(code, message, path)


class _Archive:
    def __init__(self, handle):
        self._handle = handle

    def has_file(self, inner):
        # A missing archived file is a normal false result, as in pympq.
        return bool(_storm.SFileHasFile(self._handle, _text(inner)))

    def extract_file(self, inner, dest):
        if not _storm.SFileExtractFile(self._handle, _text(inner), _text(dest),
                                       SFILE_OPEN_FROM_MPQ):
            _raise_storm_error("SFileExtractFile", os.fspath(dest))

    def add_file(self, src, inner, flags, compression):
        if not _storm.SFileAddFileEx(
                self._handle, _text(src), _text(inner), _flags(flags),
                _flags(compression), MPQ_COMPRESSION_NEXT_SAME):
            _raise_storm_error("SFileAddFileEx", os.fspath(src))

    def close(self):
        if self._handle is None:
            return
        handle = self._handle
        self._handle = None
        if not _storm.SFileCloseArchive(handle):
            _raise_storm_error("SFileCloseArchive")


def open_archive(path, locale=None):
    handle = _HANDLE()
    if not _storm.SFileOpenArchive(_text(path), 0, MPQ_OPEN_READ_ONLY,
                                   ctypes.byref(handle)):
        _raise_storm_error("SFileOpenArchive", os.fspath(path))
    return _Archive(handle)


def create_archive(path, flags, max_file_count):
    handle = _HANDLE()
    if not _storm.SFileCreateArchive(_text(path), _flags(flags),
                                     int(max_file_count), ctypes.byref(handle)):
        _raise_storm_error("SFileCreateArchive", os.fspath(path))
    return _Archive(handle)
