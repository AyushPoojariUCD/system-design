# 📌 URL Shortener 

A scalable and high-performance **URL Shortener service** (like TinyURL/Bitly) built with system design principles in mind.  
Supports **short URL generation, redirection, caching, and analytics**.  

---

## 🚀 Features
- Generate short URLs (Base62 encoding of unique IDs).  
- Redirect to the original long URL with low latency.  
- Custom aliases & optional expiry time.  
- Redis caching for fast lookups.  
- CDN edge caching for global performance.  
- Analytics (click tracking, geo, device).  
- RESTful API design (JSON-based).  
- Secure: spam detection, rate limiting, input sanitization.  

---

