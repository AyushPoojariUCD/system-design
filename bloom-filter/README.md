# Bloom Filter

A **Bloom Filter** is a **probabilistic data structure** that is used to test whether an element is a member of a set.  
It is **space-efficient** and very **fast**, but it can return **false positives** (may say an element exists when it doesn’t).  
It **never returns false negatives** (if it says "not present", the element is definitely not present).

---

## ⚡ Key Properties
- Space-efficient data structure.
- O(1) insert and lookup.
- May give **false positives**.
- **Never gives false negatives**.

---

## 🧩 How It Works
- A Bloom Filter is a **bit array** of size `m`, initialized to all zeros.
- Uses `k` independent **hash functions**.
- **Insert**: Hash the element with `k` functions → set those bit positions to `1`.
- **Query**: Check those positions:
  - If all are `1` → element **probably exists**.
  - If any is `0` → element **definitely does not exist**.

---

## 📊 Example

```

Bit array (m = 10, k = 3):

Insert "apple" → hash1=2, hash2=5, hash3=8 → set bits[2], bits[5], bits[8] = 1
Insert "banana" → hash1=1, hash2=5, hash3=7 → set bits[1], bits[5], bits[7] = 1

Check "apple":
→ all 3 bits set → probably exists
Check "mango":
→ one bit is 0 → definitely not present

```

---

## 📌 Where Bloom Filters Are Used
- **Databases / Storage**: Cassandra, HBase, LevelDB use Bloom filters to check if a key exists in an SSTable before hitting disk.  
- **Web Caching**: Avoid unnecessary cache lookups.  
- **Spam Filters**: Detect if an email is from a known spammer.  
- **Web Crawlers**: Avoid re-crawling the same URL.  
- **Networking**: Bitcoin nodes, proxies, CDNs.  
- **Big Data Systems**: Spark/Hive for efficient joins.

---

## ⚖️ Pros & Cons

✅ Pros:
- Very space-efficient.
- Fast (O(1) insert & lookup).
- No false negatives.

❌ Cons:
- False positives possible.
- Cannot delete (basic Bloom filter).
- Requires good hash functions.

---