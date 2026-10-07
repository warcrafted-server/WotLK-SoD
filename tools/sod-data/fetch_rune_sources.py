#!/usr/bin/env python3
"""Collects where each SoD rune is obtained from Wowhead (item pages), resumable.

Wowhead throttles after ~25 pages, so requests are spaced out and the run stops on
HTTP 403/429 instead of hammering. Results are cached in datos/wowhead/ (git-ignored).
"""
import csv, json, os, re, sys, time, collections
from urllib.request import Request, urlopen
from urllib.error import HTTPError

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CAT = os.path.join(ROOT, "docs/runas/catalogo-sod.json")
SPARSE = os.path.join(ROOT, "datos/wago/1.15.9.70003/ItemSparse.enUS.csv")
CACHE = os.path.join(ROOT, "datos/wowhead")
OUT = os.path.join(ROOT, "docs/runas/fuentes-sod.json")
SLOT_IDS = {399954, 399966, 399967, 417346, 415449, 415450, 417345, 417347}
UA = "Mozilla/5.0 (X11; Linux x86_64) Gecko/20100101 Firefox/130.0"
PAUSE = float(os.environ.get("PAUSE", "9"))

def fetch(kind, ident):
    os.makedirs(CACHE, exist_ok=True)
    path = os.path.join(CACHE, "%s-%s.html" % (kind, ident))
    if os.path.exists(path) and os.path.getsize(path) > 2000:
        return open(path, encoding="utf-8", errors="ignore").read()
    time.sleep(PAUSE)
    req = Request("https://www.wowhead.com/classic/%s=%s" % (kind, ident), headers={"User-Agent": UA})
    try:
        html = urlopen(req, timeout=40).read().decode("utf-8", "ignore")
    except HTTPError as exc:
        if exc.code == 404:
            open(path, "w", encoding="utf-8").write("<html>404</html>" + " " * 2100)
            return ""
        if exc.code in (403, 429):
            print("STOP: HTTP %d (rate limit). Re-run later; the cache keeps progress." % exc.code)
            sys.exit(2)
        raise
    open(path, "w", encoding="utf-8").write(html)
    return html

def listview(html, lid):
    m = re.search(r"id: '%s',.*?data: (\[.*?\]),?\s*\}\);" % re.escape(lid), html, re.S)
    if not m:
        return []
    try:
        return json.loads(m.group(1))
    except ValueError:
        return []

def sources(html):
    out = {}
    for lid, key in (("dropped-by", "drops"), ("sold-by", "vendors"), ("reward-from-q", "quests"),
                     ("contained-in-object", "objects"), ("contained-in-item", "items"),
                     ("pickpocketed-from", "pickpocket"), ("created-by-spell", "created")):
        rows = listview(html, lid)
        if rows:
            out[key] = [{k: r.get(k) for k in ("id", "name", "count", "outof", "minlevel", "maxlevel",
                                               "location", "cost", "side", "level", "reqlevel", "category")
                         if k in r} for r in rows[:12]]
    return out

def rune_items():
    """learn-rune spell id -> item ids, via item -> use spell (effect 54 enchant) -> enchant arg."""
    wago = os.path.join(ROOT, "datos/wago/1.15.9.70003")
    ench = {}
    for r in csv.DictReader(open(os.path.join(wago, "SpellItemEnchantment.enUS.csv"), encoding="utf-8")):
        ench[int(r["ID"])] = int(r["EffectArg_0"] or 0)
    spell_ench = {}
    for r in csv.DictReader(open(os.path.join(wago, "SpellEffect.enUS.csv"), encoding="utf-8")):
        if r["Effect"] == "54":
            spell_ench[int(r["SpellID"])] = int(r["EffectMiscValue_0"] or 0)
    out = collections.defaultdict(list)
    for r in csv.DictReader(open(os.path.join(wago, "ItemEffect.enUS.csv"), encoding="utf-8")):
        e = spell_ench.get(int(r["SpellID"]))
        if e and ench.get(e):
            out[ench[e]].append(int(r["ParentItemID"]))
    return out

def main():
    links = rune_items()
    names = collections.defaultdict(list)
    for r in csv.DictReader(open(SPARSE, encoding="utf-8")):
        names[(r.get("Display_lang") or "").lower()].append(int(r["ID"]))
    only = os.environ.get("CLASS")
    runes = [r for r in json.load(open(CAT, encoding="utf-8"))["runas"]
             if r["slot_id"] in SLOT_IDS and (not only or r["clase"] == only)]
    result = json.load(open(OUT, encoding="utf-8")) if os.path.exists(OUT) else {}
    limit = int(os.environ.get("LIMIT", "0"))
    done = 0
    for r in runes:
        key = str(r["taught_spell_id"])
        if key in result and result[key].get("estado") == "ok":
            continue
        if limit and done >= limit:
            break
        n = (r["name_en"] or "").lower()
        ids = list(links.get(r["learn_spell_id"], [])) + list(links.get(r["taught_spell_id"], []))
        entry = {"runa": r["name_en"], "clase": r["clase"], "ranura": r["slot"], "objetos": []}
        if not ids:
            html = fetch("spell", r["taught_spell_id"])
            ids = [row["id"] for row in listview(html, "used-by-item") if row.get("id")]
            if ids:
                entry["objeto_segun_wowhead"] = "used-by-item"
        if not ids:
            html = fetch("spell", r["taught_spell_id"])
            m = re.search(r'<meta name="description" content="([^"]*?) teaches this', html)
            if m:
                ids = names.get(m.group(1).lower(), [])
                entry["objeto_segun_wowhead"] = m.group(1)
        for iid in ids[:2]:
            html = fetch("item", iid)
            title = re.search(r"<title>([^<]*)</title>", html)
            entry["objetos"].append({"id": iid, "titulo": title.group(1) if title else None, **sources(html)})
        entry["estado"] = "ok" if entry["objetos"] else "sin_objeto"
        result[key] = entry
        done += 1
        json.dump(result, open(OUT, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
        print("%s -> %s" % (r["name_en"], [o["id"] for o in entry["objetos"]]), flush=True)
    json.dump(result, open(OUT, "w", encoding="utf-8"), ensure_ascii=False, indent=1)

if __name__ == "__main__":
    main()
