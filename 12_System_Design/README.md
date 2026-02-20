# 12 · System Design
> **Comprehensive Guide · ~120 min · Patterns: Scalability, Microservices, OOD**

System Design interviews test your ability to build large-scale, high-availability, and fault-tolerant software systems. While algorithms test your micro-level coding, system design tests your macro-level architecture and Object-Oriented Design (OOD) skills.

This module acts as the capstone to the repository, transforming it from a coding practice repo into a full-stack MAANG resource hub.

---

## Unit Map

| Unit | Title | Time |
|------|-------|------|
| [12.1](#121-intro) | Intro — Why System Design Matters | 5 min |
| [12.2](#122-the-framework) | The 4-Step Interview Framework | 10 min |
| [12.3](#123-core-concepts--scalability) | Core Concepts: Scalability (Vertical vs Horizontal) | 5 min |
| [12.4](#124-core-concepts--load-balancers) | Core Concepts: Load Balancers & Caching | 10 min |
| [12.5](#125-core-concepts--databases) | Core Concepts: Databases (SQL, NoSQL, Sharding) | 10 min |
| [12.6](#126-core-concepts--microservices) | Core Concepts: Microservices & Message Queues | 10 min |
| [12.7](#127-core-concepts--cap-theorem) | Core Concepts: The CAP Theorem & Consistent Hashing | 10 min |
| [12.8](#128-core-concepts--networks) | Core Concepts: Network Protocols, APIs & CDNs | 10 min |
| [12.9](#129-core-concepts--proxies) | Core Concepts: Proxies, Rate Limiting & Security | 10 min |
| [12.10](#1210-mock-design--url-shortener) | Mock Design: URL Shortener (TinyURL) | 15 min |
| [12.11](#1211-mock-design--news-feed) | Mock Design: Twitter / News Feed | 15 min |
| [12.12](#1212-mock-design--chat-system) | Mock Design: Chat System (WhatsApp / Discord) | 15 min |
| [12.13](#1213-mock-design--streaming) | Mock Design: YouTube / Netflix | 15 min |
| [12.14](#1214-mock-design--key-value-store) | Mock Design: Distributed Key-Value Store | 15 min |
| [12.15](#1215-mock-design--location) | Mock Design: Location-Based Service (Yelp / Uber) | 15 min |
| [12.16](#1216-object-oriented-design) | Object-Oriented Design (OOD) & SOLID | 15 min |
| [12.17](#1217-common-interview-qa) | Common Interview Q&A | 10 min |
| [12.18](#1218-recap) | Final Recap | 5 min |

---

## 12.1 Intro
**Why System Design Matters · 5 min**

In junior interviews (L3), algorithmic coding is 90% of the focus. For mid-level (L4) and senior (L5+) roles at MAANG, System Design becomes the deciding factor.

**What they look for:**
- **Ambiguity navigation:** Can you take a vague prompt ("Design YouTube") and translate it into strict technical requirements?
- **Trade-off awareness:** Do you understand that no system is perfect? (e.g., choosing strong consistency vs high availability).
- **Domain knowledge:** Do you know when to use Redis vs Postgres vs Cassandra?

System design is not about finding the "correct" answer; it's about justifying the design choices you make.

---

## 12.2 The Framework
**The 4-Step Interview Framework · 10 min**

Never start drawing boxes immediately. Follow this structured 45-minute progression:

### Step 1: Understand the Problem & Establish Scope (5-7 min)
Clarify requirements. Ask targeted questions.
- **Functional Requirements:** What must the system do? (e.g., "Users can upload video", "Users can view video").
- **Non-Functional Requirements:** Scalability, High Availability, low latency.
- **Back-of-the-envelope estimation:** How many Daily Active Users (DAU)? QPS (Queries Per Second)? Storage needed per year? (Rule of thumb: 100M DAU is a standard massive scale).

### Step 2: Propose High-Level Design (10-15 min)
Draw the blueprint. Get buy-in from the interviewer.
- **Client/API Gateway:** Mobile app, web app.
- **Core Services:** User API, Feed API.
- **Data Layer:** SQL for relational data, Object Storage (S3) for media.
*You should have 3-5 distinct boxes connected by arrows.*

### Step 3: Deep Dive (15-20 min)
Focus on the most challenging component of the system.
- If designing a URL shortener: focus on the Hash generation logic and DB collisions.
- If designing a Chat app: focus on WebSockets, presence servers, and message ordering.

### Step 4: Wrap Up & Bottlenecks (3-5 min)
Identify single points of failure. Discuss future improvements if the scale increases 10x.

---

## 12.3 Core Concepts: Scalability
**Vertical vs Horizontal · 5 min**

**Vertical Scaling (Scale Up):**
- Adding more CPU/RAM to a single server.
- **Pros:** Simple. No distributed system complexity.
- **Cons:** Hard limit on hardware. Single point of failure.

**Horizontal Scaling (Scale Out):**
- Adding more servers to a resource pool.
- **Pros:** Infinite scale, robust redundancy.
- **Cons:** Requires stateless servers, Load Balancers, and distributed logic (complexity).

*Standard MAANG answer: Always scale horizontally for massive Web/App tiers.*

---

## 12.4 Core Concepts: Load Balancers & Caching
**Traffic Routing and Speed · 10 min**

### Load Balancers (LB)
Sit between the clients and the servers. They distribute incoming HTTP/WebSocket traffic across multiple servers using algorithms like Round Robin, Least Connections, or IP Hashing.
- Solves the "single point of failure" problem for the web tier.

### Caching (Redis / Memcached)
Takes load off the database by storing frequently accessed, relatively static data in memory (RAM).
- **Read-Heavy systems** (like Twitter feeds) rely entirely on caches.
- **Strategies:** Cache Aside, Read-Through, Write-Through.
- **Eviction policies:** LRU (Least Recently Used) is the standard.

---

## 12.5 Core Concepts: Databases
**SQL, NoSQL, and Sharding · 10 min**

### Relational (SQL) - PostgreSQL, MySQL
- Use when: Data has strict relationships, requires ACID transactions (banking), scheme is clear and unchanging.

### Non-Relational (NoSQL) - Cassandra, MongoDB, DynamoDB
- Use when: Massive scale horizontal sharding is needed, schema is flexible (JSON), high write throughput is required (analytics/logs).

### Database Scaling Strategies:
1. **Replication (Master-Slave):** Master takes Writes; multiple Slaves take Reads. Good for Read-heavy systems.
2. **Sharding (Partitioning):** Splitting a massive database across multiple machines (e.g., User IDs 1-1M on DB-A, 1M-2M on DB-B). High complexity, but required for massive datasets.

---

## 12.6 Core Concepts: Microservices & Message Queues
**Decoupling the System · 10 min**

### Microservices
Instead of one massive backend (Monolith), split logic into independent services (Auth Service, Notification Service, Payment Service).
- They communicate via REST or gRPC.
- Failures are isolated (if Notification goes down, Payment still works).

### Message Queues (Kafka, RabbitMQ)
Used for asynchronous communication. 
- Example: User uploads a video. The web server drops an "Upload Event" into Kafka and immediately returns `200 OK` to the user. Worker servers slowly pull from Kafka to compress/process the video in the background without holding up the HTTP request.

---

## 12.7 Core Concepts: The CAP Theorem & Consistent Hashing
**Distributed Data Trade-offs · 10 min**

### The CAP Theorem
In any distributed data store, you can only guarantee **two out of three**:
1. **Consistency (C):** All nodes see the same data at the same time.
2. **Availability (A):** Every request receives a response (even if it's stale data).
3. **Partition Tolerance (P):** The system operates despite network failures between nodes.

**Real-World Application:** Networks fail, so **P is mandatory**. You must choose between **CP** (Banking systems — better to fail a request than show wrong balance) and **AP** (Social Media — better to show a slightly outdated post count than crash the site).

### Consistent Hashing
When scaling caching servers or databases horizontally, standard hashing (`serverIndex = hash(key) % N`) breaks down catastrophically if a server is added or removed (nearly all keys must be remapped).
**Consistent Hashing solves this:**
- Map servers and keys to a conceptual "hash ring" (0 to 2^160 - 1).
- To find which server holds a key, map the key onto the ring and move clockwise to find the first server.
- Adding or removing a server only affects the keys immediately adjacent to it on the ring.
- Use **Virtual Nodes** to ensure an even distribution of keys across servers.

---

## 12.8 Core Concepts: Network Protocols, APIs & CDNs
**Moving the Data · 10 min**

### APIs & Protocols
- **REST:** Representational State Transfer. Uses standard HTTP methods (GET, POST, PUT, DELETE). JSON payloads. Stateless.
- **gRPC:** Extremely fast, uses Protocol Buffers (binary). Excellent for internal microservice-to-microservice communication.
- **WebSockets / Server-Sent Events (SSE):** Persistent connections. WebSockets are bidirectional (Chat apps). SSE is unidirectional from server to client (Live sports scores, stock tickers).

### Storage & Delivery
- **Blob / Object Storage:** Amazon S3. Used for unstructured data like videos, images, and backups. Extremely cheap and durable.
- **CDN (Content Delivery Network):** Geographically distributed network of proxy servers (Cloudflare, Akamai). They cache static assets (images, videos, JS, CSS) at the "edge", physically closer to the user to drastically reduce latency.

---

## 12.9 Core Concepts: Proxies, Rate Limiting & Security
**Protecting and Managing Traffic · 10 min**

### Proxies
- **Forward Proxy:** Sits in front of client machines. Used to hide client IPs or restrict outbound internet access (e.g., corporate VPN).
- **Reverse Proxy:** Sits in front of backend servers (e.g., Nginx, HAProxy). Used to hide server IPs, handle SSL termination, and act as a Load Balancer or API Gateway.

### Rate Limiting
Essential to prevent DDoS attacks and API abuse. Implemented in the API Gateway / Reverse Proxy.
- **Algorithms:**
  - **Token Bucket:** Tokens are added at a constant rate. Requests consume tokens. Handles bursty traffic well.
  - **Leaky Bucket:** Requests enter a queue. Processed at a constant strict rate. Good for smooth, predictable loads.
  - **Sliding Window:** Tracks timestamps of requests (down to the second). Highly accurate, but memory-intensive (often backed by Redis).

### Security
- **OAuth 2.0 / JWT:** Standard for authorization. JSON Web Tokens (JWTs) are stateless and self-contained (cryptographically signed). No backend DB lookup is required to verify the user's identity.
- **HTTPS & TLS:** Encrypts data in transit. **SSL termination** often happens at the Load Balancer to offload the heavy decryption CPU cycles from the application web servers.

---

## 12.10 Mock Design: URL Shortener
**A classic Read-Heavy architecture · 15 min**

**1. Requirements:**
- Convert long URL to short URL. Redirect short to long.
- 100M URLs generated per day. 10:1 read-to-write ratio (1 Billion reads).

**2. Storage Estimation:**
- 100M * 365 * 10 years = 365 Billion URLs.
- If each record is 100 bytes → 36.5 TB storage.

**3. High Level Design:**
- Client → Load Balancer → Web Servers.
- Web Servers talk to a Highly Available NoSQL DB (Key-Value store) for massive horizontal scaling.

**4. Deep Dive: Hash Generation:**
- Base62 encoding (A-Z, a-z, 0-9 = 62 characters).
- Length 7 gives 62^7 = 3.5 Trillion URLs (plenty for 365 Billion).
- To avoid massive DB collisions when hashing: pre-generate Keys using a clustered **Ticket Server** (like Twitter Snowflake) that guarantees unique auto-incrementing IDs, then convert the ID to Base62.

---

## 12.11 Mock Design: News Feed
**Design Twitter / Instagram Feed · 15 min**

**1. Requirements:**
- Users can publish posts and view feeds of people they follow. Fast feed loading.

**2. High Level Design:**
- Two massive flows: **Feed Publishing API** and **Feed Retrieval API**.

**3. Deep Dive: Fanout Strategy:**
- **Fanout on Write (Push):** When User A posts, the system computes the feeds of all their followers and pushes the post to their in-memory Redis caches. 
  - *Pro:* Read is instantly O(1). 
  - *Con:* The "Justin Bieber problem" — if a celeb has 100M followers, a single post triggers 100M database operations.
- **Fanout on Read (Pull):** When a user loads their feed, the system fetches posts from everyone they follow and merges them at runtime.
  - *Pro:* Good for massive celebrities.
  - *Con:* High latency for average users.
- **Optimal Solution:** Hybrid. Use Push for normal users, use Pull for celebrities (threshold > 100k followers).

---

## 12.12 Mock Design: Chat System
**Design WhatsApp / Discord · 15 min**

**1. Requirements:**
- 1-on-1 chatting, group chatting. Low latency message delivery. Online presence.

**2. High Level Design:**
- **Stateless Services:** Login, API gateway, User Profile retrieval.
- **Stateful Services:** The Chat Servers. These hold persistent connections to clients.

**3. Deep Dive: Connections & Delivery:**
- HTTP is unidirectional (Client asks Server). Unsuitable for chat.
- Use **WebSockets** for persistent, bidirectional connections.
- When User A sends to B: A talks to Chat Server 1. CS1 checks a **Redis Routing Cache** to see which Server User B is connected to (e.g., CS4). CS1 forwards the message over internal RPC to CS4, which pushes it down the WebSocket to User B.
- Use a **Message Queue** for offline users to guarantee delivery upon reconnection.

---

## 12.13 Mock Design: YouTube / Netflix
**Heavy Blob Storage and Streaming · 15 min**

**1. Requirements:**
- Users can upload videos. Users can stream videos smoothly. High availability.

**2. High Level Design:**
- This requires splitting the system into two distinct workflows: **Video Uploading** and **Video Streaming**.

**3. Deep Dive: Upload Flow:**
- User uploads raw video to original storage (S3).
- **Message Queue:** An upload completion event is dropped into Kafka.
- **Transcoding Workers:** Worker servers pull the event, fetch the original video, and transcode it into multiple bitrates/formats (1080p, 720p, 480p, HLS/DASH formats) in parallel.
- Transcoded videos are stored in S3, and metadata (title, URL) is saved in the Database.

**4. Deep Dive: Streaming Flow:**
- The key to video streaming is the **CDN**. 
- Users request a video. The request hits the nearest CDN edge server. If cached, it streams instantly with minimal latency. If not, the CDN fetches it from S3, caches it, and streams it.
- Never stream directly from application web servers.

---

## 12.14 Mock Design: Distributed Key-Value Store
**Designing DynamoDB/Cassandra · 15 min**

**1. Requirements:**
- `put(key, value)`, `get(key)`. Highly available (AP system), highly scalable.

**2. Core Architecture:**
- **Data Partitioning:** Use **Consistent Hashing** (with virtual nodes) to distribute keys across a ring of servers.
- **Data Replication:** Replicate data across N sequential nodes on the hash ring to guarantee durability if a node dies.
- **Consistency vs Availability:** Use a Quorum consensus. If N=3 (3 replicas), Write Quorum (W)=2, Read Quorum (R)=2. `W + R > N` guarantees strong consistency. If `W=1`, writes are extremely fast but reads might be stale (Eventual Consistency).

**3. Deep Dive: Handling Failures:**
- **Failure Detection:** Nodes use a **Gossip Protocol** to ping each other and build a decentralized map of healthy/dead nodes.
- **Write Failures (Hinted Handoff):** If node A is dead, node B temporarily accepts its writes. When A recovers, B hands the data back.
- **Read Failures (Read Repair & Anti-Entropy):** Use **Merkle Trees** to quickly compare chunks of data between replicas to fix inconsistencies in the background.

---

## 12.15 Mock Design: Location-Based Service (Yelp / Uber)
**Handling Spatial Data and Proximity · 15 min**

**1. Requirements:**
- Given a user's (Latitude, Longitude), find the top K closest drivers or restaurants within an N-mile radius. High read volume (Yelp) or high write volume (Uber drivers reporting locations every 3 seconds).

**2. Core Problem: 2D Spatial Searches**
- Standard SQL queries (`WHERE lat BETWEEN x AND y AND long BETWEEN w AND z`) are incredibly slow at scale because you cannot easily index two independent columns to compute a 2D bounding box intersection efficiently.

**3. Deep Dive: Spatial Indexing Solutions**
- **Geohashing:** Converts a 2D (Lat, Long) into a 1D string (e.g., `9q8yy`). The world is mapped as a grid. Continually dividing grid quadrants adds characters to the string. 
  - *Key Property:* Locations that are close together often share the exact same string prefix. You can find nearby places extremely fast by doing substring prefix matching (`LIKE '9q8%'`) using a standard database B-Tree index.
- **QuadTrees:** An in-memory tree building data structure where each node represents a bounding box on a map. If a box has too many locations (>50), it recursively splits into 4 child quadrants. This allows incredibly fast O(log N) proximity searches. It is often kept entirely in RAM across multiple servers.

**4. Handling Uber's Massive Write Volume:**
- Since drivers move constantly, updating a DB index or QuadTree every 3 seconds per driver destroys the database. 
- *Optimal Solution:* Drivers constantly push location data to an **In-memory cache (Redis)** first. A background job / queue consumes the cache to update the persistent Spatial Database / QuadTree in optimized batches (e.g., every 30 seconds).

---

## 12.16 Object-Oriented Design
**OOD & SOLID Principles · 15 min**

Often asked as a bridge between Algorithms and Systems (e.g., "Design a Parking Lot"). This tests OOP logic, abstract classes, encapsulation, and C#/C++ skills.

### The SOLID Principles
1. **Single Responsibility:** A class should have one job. (Don't put DB logic inside your `User` model).
2. **Open/Closed:** Classes are open for extension (inheritance), closed for modification (don't rewrite the core class to add a feature).
3. **Liskov Substitution:** Derived classes must be substitutable for their base classes.
4. **Interface Segregation:** Better to have many small interfaces (`IFlyable`, `ISwimmable`) than one giant interface (`IAnimal`).
5. **Dependency Inversion:** Depend on abstractions (Interfaces), not concretions. Instead of instantiating `SqlDb` directly, inject `IDatabase`.

### Common OOD Patterns
- **Singleton:** Ensuring only one instance (e.g., a shared Database Connection Pool).
- **Factory:** Let subclasses decide which object to instantiate (e.g., UI Buttons).
- **Strategy:** Define a family of algorithms, encapsulate them, and make them interchangeable at runtime (e.g., swapping Sorting algorithms).

---

## 12.17 Common Interview Q&A
**Rapid-Fire Trade-offs & Architecture Decisions · 10 min**

These are the most common follow-up and push-back questions you will face during a MAANG System Design interview.

**Q1. "Your database is getting hammered with reads. How do you scale it?"**
*Answer:* I would introduce a **caching layer** (Redis/Memcached) using a Cache-Aside strategy. If the cache is cold or the data changes, I'll update it. If reads are still too high, I will implement **Read Replicas** (Master-Slave architecture), routing all `SELECT` statements to the replicas and `INSERT/UPDATE` to the Master.

**Q2. "What if your caching server (Redis) crashes?"**
*Answer:* If I'm using a single Redis instance, all traffic falls back to the primary DB, which might cause a **Thunder Herd** stampede and crash the DB. To prevent this, I would deploy a **Redis Cluster** across multiple AZs (Availability Zones) using Consistent Hashing. If one node dies, the others distribute the load.

**Q3. "We need to scale writes, not just reads. What do we do?"**
*Answer:* Read replicas don't help with writes. I need to **Shard (Partition)** the database horizontally. I'd split the data logically (e.g., User IDs 1-1M go to Database A, IDs 1M-2M go to Database B). I would use a consistent hashing ring to handle dynamic sharding if a single shard gets too "hot" (e.g., Justin Bieber's shard).

**Q4. "How do you handle a single 'Hot Key' bringing down a server?"**
*(Context: A celebrity tweets, and 50 million people request the same Cache Node.)*
*Answer:* A single server can only handle so much network bandwidth. To solve this, I would add a **Local Cache** (like Guava in Java or memory caches in Node) directly onto my application servers for just those highly viral keys, bypassing the Redis network hop entirely. I could also prepend random numbers to the key to duplicate it across multiple Redis nodes.

**Q5. "Why would you choose Cassandra over PostgreSQL for this?"**
*Answer:* PostgreSQL guarantees ACID transactions and strong consistency (CP system). However, for a Massive logging system or WhatsApp messaging history, we write billions of rows a day and don't need strict relational joins. Cassandra is a wide-column NoSQL store designed for **extreme write-throughput** and High Availability (AP system), making it far superior for this specific workload.

**Q6. "How do you guarantee a notification/payment is sent EXACTLY once?"**
*Answer:* "Exactly-once" delivery in distributed systems is mythic due to network unreliability. You can only guarantee **"At-least-once"**. To simulate "Exactly-once", I must make the receiver **Idempotent**. I would generate a unique `Idempotency-Key` (UUID) for the payment on the client side. The server checks the DB for this key. If it exists, it ignores the duplicate request. If it doesn't, it processes the payment and saves the key.

**Q7. "What happens if our Message Queue (Kafka/RabbitMQ) gets backed up?"**
*Answer:* I would immediately scale up the number of worker instances consuming from the queue. If we are using Kafka, I must ensure that I also increase the number of **Partitions** in the Kafka Topic, because a single partition can only be consumed by one worker in a consumer group at a time. I would also set up an alerting threshold (e.g., if queue depth > 10,000, trigger PagerDuty).

**Q8. "How do you ensure global users get low latency?"**
*Answer:* I would use a **CDN** for all static assets (images, React bundles, videos) to serve them from Edge nodes. For dynamic API calls, I would deploy my application servers in multiple geographical regions (AWS US-East, EU-West, AP-South) and use **Geo-Routing** at the DNS/Load Balancer level to route users to their physically closest data center.

---

## 12.18 Recap

**System Design is about surviving trade-offs:**
- SQL guarantees consistency but scales poorly horizontally.
- NoSQL scales infinitely horizontally but gives up complex relationships.
- Push models make reads fast but writes heavy.
- Pull models make writes fast but reads slow.

*Speak your trade-offs continuously during the interview. That is the true test of a senior engineer.*

---
*End of roadmap. You have completed the ultimate MAANG preparation guide.*

