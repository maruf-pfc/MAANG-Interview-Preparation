# 12 · System Design
> **The Definitive Guide · ~240 min · Patterns: Scalability, Microservices, OOD, Distributed Systems**

System Design interviews test your ability to build large-scale, high-availability, and fault-tolerant software systems. While algorithms test your micro-level coding, system design tests your macro-level architecture, trade-off awareness, and domain knowledge.

This is the most critical module for Mid-Level (L4) and Senior (L5+) engineering roles at Meta, Amazon, Apple, Netflix, and Google.

---

## 🗺️ Unit Map

| Unit | Title | Focus |
|------|-------|-------|
| [12.1](#121-intro) | Intro & The 4-Step Framework | Ambiguity navigation & scoping |
| [12.2](#122-capacity-planning) | Capacity Planning & Back-of-the-Envelope Math | QPS, Storage, Bandwidth, Latency |
| [12.3](#123-networking) | Networking & Protocols | TCP/UDP, HTTP/3, WebSockets, gRPC |
| [12.4](#124-proxies-lb) | Proxies & Load Balancing | L4 vs L7, Nginx, Hashing Algorithms |
| [12.5](#125-databases) | Databases & Storage | SQL vs NoSQL, Sharding, Replication, Indexing |
| [12.6](#126-caching) | Caching Strategies | Cache-aside, Write-through, Eviction, Redis |
| [12.7](#127-messaging) | Messaging & Queues | Kafka vs RabbitMQ, Event-Driven Arch |
| [12.8](#128-distributed-theory) | Distributed Systems Core Theory | CAP, PACELC, Gossip, Quorum, Raft |
| [12.9](#129-security) | Security & Reliability | JWT, OAuth, Rate Limiting, Circuit Breakers |
| [12.10](#1210-mock-url) | Mock Design: URL Shortener (TinyURL) | Base62, Collision avoidance, Ticket Servers |
| [12.11](#1211-mock-feed) | Mock Design: News Feed (Twitter) | Fanout-on-write vs Fanout-on-read |
| [12.12](#1212-mock-chat) | Mock Design: Chat System (WhatsApp) | WebSockets, Presence Servers, Syncing |
| [12.13](#1213-mock-kv) | Mock Design: Distributed Key-Value Store | Consistent Hashing, Hinted Handoff |
| [12.14](#1214-mock-video) | Mock Design: Video Streaming (YouTube) | CDNs, Transcoding DAGs, Blob Storage |
| [12.15](#1215-mock-location) | Mock Design: Location Service (Uber/Yelp) | QuadTrees, Geohashing, Spatial DBs |
| [12.16](#1216-mock-limiter) | Mock Design: Distributed Rate Limiter | Token/Leaky Buckets, Redis Lua Scripts |
| [12.17](#1217-mock-booking) | Mock Design: Ticketmaster / Hotel Booking | Concurrency, Distributed Locks, Sagas |
| [12.18](#1218-mock-crawler) | Mock Design: Web Crawler | BFS, Politeness, URL Frontier, Bloom Filters |
| [12.19](#1219-ood) | Object-Oriented Design (OOD) | SOLID, Design Patterns (Singleton, Factory) |
| [12.20](#1220-qa) | The MAANG Q&A Bank | 15 Rapid-fire trade-off survival questions |

---

## 12.1 Intro & The 4-Step Framework
**Why System Design Matters**

In junior interviews, algorithmic coding is the focus. For mid/senior roles, System Design is the deciding factor. They look for:
- **Ambiguity navigation:** Extracting strict technical requirements from "Design YouTube".
- **Trade-off awareness:** Knowing that no system is perfect. (e.g., choosing strong consistency destroys high availability).
- **Domain knowledge:** Knowing when to use Redis vs Postgres vs Cassandra vs Kafka.

### The 4-Step Interview Framework (45 min)

Never start drawing immediately. Follow this progression:

**Step 1: Understand the Problem & Establish Scope (5-7 min)**
- **Functional Requirements:** What MUST the system do? (e.g., "Users can upload video", "Users can view video").
- **Non-Functional Requirements:** Highly Available? Low latency? Strongly consistent?
- *Never assume.* Ask: "Are we focusing on mobile or web? Is this global or regional? Do we need analytics?"

**Step 2: Back-of-the-envelope estimation (3-5 min)**
- Compute QPS (Queries Per Second).
- Compute Storage per year.
- Compute Network Bandwidth.

**Step 3: Propose High-Level Design (10-15 min)**
- Draw the blueprint. Client → Load Balancer → API Gateway → Web Servers → Database / Cache.
- Get buy-in from the interviewer before detailing any single box.

**Step 4: Deep Dive & Bottlenecks (15-20 min)**
- Focus on the hardest component.
- If Twitter: Focus on the Feed Fanout logic.
- If WhatsApp: Focus on WebSocket connection management.
- Discuss Single Points of Failure (SPOF) and how to fix them.

---

## 12.2 Capacity Planning & Back-of-the-Envelope Math
**Numbers Every Software Engineer Should Know**

Interviewers expect you to estimate load quickly without a calculator. 

### standard Latency numbers (Jeff Dean)
- L1 cache reference: `0.5 ns`
- Mutex lock/unlock: `100 ns`
- Main memory reference (RAM): `100 ns`
- Read 1 MB sequentially from memory: `250,000 ns` (0.25 ms)
- Round trip within same datacenter: `500,000 ns` (0.5 ms)
- Disk seek: `10,000,000 ns` (10 ms)
- Read 1 MB sequentially from Network: `10 ms`
- Read 1 MB sequentially from Disk: `30 ms`
- Send packet CA to Netherlands to CA: `150 ms`

### Data Size Estimations
- Char/Boolean: `1 byte`
- Integer: `4 bytes`
- Timestamp/Float64: `8 bytes`
- UUID: `16 bytes`
- Short Text (Tweet): `140 - 200 bytes`
- Image: `200 KB - 2 MB`
- Video: `50 MB - 100+ MB`

### Quick Math Rules
- `1 Million requests / day` ≈ `12 QPS`.
- `100 Million requests / day` ≈ `1,200 QPS`.
- `1 Billion requests / day` ≈ `12,000 QPS`.
- Storage: `1 KB * 1 Billion` = `1 TB`.

**Example:** *Design Twitter. 300M Daily Active Users. 10% tweet once a day. 100% read 100 tweets a day.*
- **Write QPS:** 30M tweets / 86400 sec ≈ 350 writes/sec.
- **Read QPS:** 300M * 100 / 86400 ≈ 350,000 reads/sec. *(Massively read heavy! Requires aggressive caching).*

---

## 12.3 Networking & Protocols
**Moving the Data**

### OSI Model Highlights
- **Layer 4 (Transport):** TCP (Transmission Control Protocol - reliable, ordered, error-checked, requires 3-way handshake) vs UDP (User Datagram Protocol - fire and forget, fast, unordered, used in video streaming/gaming).
- **Layer 7 (Application):** HTTP, WebSockets, DNS.

### HTTP Evolution
- **HTTP/1.1:** Keep-alive connections, but suffers from Head-of-Line (HOL) blocking.
- **HTTP/2:** Multiplexing (multiple requests over one TCP connection), binary framing, server push.
- **HTTP/3 (QUIC):** Built on UDP instead of TCP. Eliminates TCP head-of-line blocking, vastly faster connection setup (0-RTT).

### API Paradigms
- **REST:** Representational State Transfer. Standard HTTP verbs (GET, POST, PUT, DELETE), stateless, JSON payloads. Standard for public APIs.
- **gRPC:** Remote Procedure Call by Google. Uses Protocol Buffers (binary). Strongly typed, extremely fast, bi-directional streaming. *Standard for internal microservice communication.*
- **GraphQL:** Client specifies exactly what data it wants. Fixes over-fetching/under-fetching of REST.

### Real-Time Communication
- **Long Polling:** Client requests, server holds connection open until data is ready. High overhead.
- **WebSockets:** Persistent, bi-directional, full-duplex TCP connection. (Standard for Chat/Gaming).
- **Server-Sent Events (SSE):** Persistent, unidirectional (Server -> Client). Good for live stock tickers, sports scores.

---

## 12.4 Proxies & Load Balancing
**Directing the Traffic**

### Proxies
- **Forward Proxy:** Sits in front of clients. Hides client IPs, enforces corporate firewalls.
- **Reverse Proxy:** Sits in front of backend servers (e.g., Nginx, HAProxy, Envoy). Hides server IPs, performs SSL termination, compression, and acts as an entry point.

### Load Balancers (LBs)
LBs distribute incoming traffic to prevent any single server from failing under load.
- **L4 Load Balancer:** Routes traffic based on IP address and Port (TCP/UDP level). Very fast, cannot look at HTTP headers.
- **L7 Load Balancer:** Looks inside the HTTP payload (Headers, Cookies, URL paths). Can route `/video` to Video Servers and `/text` to Text Servers.

### LB Algorithms
1. **Round Robin:** Sequential routing. Great if all servers are identical.
2. **Least Connections:** Routes to the server with the fewest active connections. Good for long-lived WebSockets.
3. **IP Hashing:** Hash the client's IP. Ensures the same client always hits the same server (Sticky Sessions).
4. **Consistent Hashing:** Explained in detail in Section 12.8. Essential for distributed caches.

---

## 12.5 Databases & Storage
**The Heart of the System**

### Relational Databases (SQL - PostgreSQL, MySQL)
- Structured data, predefined schemas.
- Adhere to **ACID** properties (Atomicity, Consistency, Isolation, Durability).
- Use when: Data has strict relationships (Banking, E-commerce transactions, Inventory).
- **Downside:** Hard to scale horizontally. Usually scaled via Master-Slave Read Replicas.

### Non-Relational Databases (NoSQL)
- Adhere to **BASE** properties (Basically Available, Soft state, Eventual consistency).
- **Key-Value (Redis, DynamoDB):** Fast O(1) lookups. Good for sessions, caches, carts.
- **Wide-Column (Cassandra, HBase):** Massively horizontal, extreme write-throughput. Good for time-series, logs, chat history.
- **Document (MongoDB, Couchbase):** Flexible JSON schemas. Good for catalogues, content management.
- **Graph (Neo4j):** Nodes and edges. Good for recommendation engines, friend networks.

### Scaling Databases
1. **Vertical Scaling:** Buy a bigger machine. Will hit a ceiling.
2. **Replication (Master-Slave):** Master takes Writes, Slaves take Reads. Solves read-heavy scaling.
3. **Sharding (Horizontal Partitioning):** Splitting data across multiple machines based on a Shard Key (e.g., Hash(UserID) % N). Extremely complex (Resharding data, solving "celebrity" hot keys, cross-shard joins are impossible).

### Indexing
- **B-Trees:** Standard SQL index. Optimized for fast reads. Updates require re-balancing the tree.
- **LSM-Trees (Log-Structured Merge-Tree) & SSTables:** Standard in Cassandra/RocksDB. Optimized for extreme write speeds by appending to sequential logs in memory, then flushing to disk.

---

## 12.6 Caching Strategies
**Eliminating Database Latency**

Caches (Redis, Memcached) store frequently accessed data in RAM, returning it in <1ms instead of hitting a 30ms DB query.

### Caching Patterns
1. **Cache-Aside:** Application checks cache. If miss, app reads from DB, writes to cache, returns to user. (Most common).
2. **Read-Through:** App asks Cache for data. Cache is responsible for fetching from DB if it's missing.
3. **Write-Through:** App writes to Cache. Cache immediately writes to DB synchronously. Safe, but slow writes.
4. **Write-Back (Write-Behind):** App writes to Cache. Cache ACKs immediately. Cache async writes to DB later. Very fast, but risks data loss if cache crashes before DB sync.

### Eviction Policies
When RAM is full, what gets deleted?
- **LRU (Least Recently Used):** Delete the oldest accessed item. (Standard).
- **LFU (Least Frequently Used):** Delete the item with the fewest total accesses.
- **TTL (Time To Live):** Hard expiration (e.g., 60 seconds).

---

## 12.7 Messaging & Queues
**Asynchronous Decoupling**

To keep HTTP requests fast, push heavy processing to the background.
If a user uploads a video, the web server puts an `UploadEvent` in a Message Queue and returns `200 OK`. Background Workers pull from the queue to transcode the video.

### The Heavyweights
- **RabbitMQ:** "Smart broker, dumb consumer". Uses routing exchanges. Pushes messages to consumers. Good for complex routing, priority queues.
- **Kafka:** "Dumb broker, smart consumer". A distributed append-only log. Messages are persisted to disk. Consumers track their own offsets. Insanely scalable (Millions of msgs/sec). Good for event sourcing, stream processing, massive telemetry.

### Delivery Guarantees
- **At-most-once:** Fire and forget. Might lose message.
- **At-least-once:** Retries until ACK'd. Might process message twice (Requires consumers to be **Idempotent**).
- **Exactly-once:** Mathematically impossible in a strictly distributed system without massive performance hits, though Kafka offers transactional guarantees to simulate it.

---

## 12.8 Distributed Systems Core Theory
**The Math Behind the Magic**

### The CAP Theorem
In a distributed data store, you can only guarantee TWO of the following THREE:
1. **Consistency (C):** All nodes return the exact same, most recent data.
2. **Availability (A):** Every request receives a non-error response.
3. **Partition Tolerance (P):** The system continues to operate despite network drops between nodes.

*Because network partitions (P) are inevitable, you MUST choose between CP or AP.*
- **CP Protocol:** (e.g., HBase, MongoDB). If a network splits, the system blocks requests rather than serving stale data. Good for Bank balances.
- **AP Protocol:** (e.g., Cassandra, Dynamo). If a network splits, the system serves stale data to remain available. Good for Reddit upvotes.

### PACELC Theorem
An extension of CAP. If there is a Partition (P), you must choose (A) or (C). Else (E), during normal operation, you must choose between Latency (L) and Consistency (C).

### Consistent Hashing
If you scale out 5 cache servers, standard hashing (`key % 5`) means if you add a 6th server, 80% of your keys map to the wrong server, causing a cache miss avalanche.
**Solution:**
- Map servers and data keys to a circular "Hash Ring" (0 to 360 degrees).
- To find a key's server, walk clockwise until you hit a server.
- Adding a server only disrupts the keys immediately adjacent to it.
- **Virtual Nodes:** Add 100 virtual labels for each real server onto the ring to statistically guarantee perfectly even load distribution.

### Gossip Protocol & Merkle Trees
- **Gossip Protocol:** Decentralized peer-to-peer communication. Nodes randomly ping other nodes ("gossip") to figure out who is alive/dead.
- **Merkle Trees (Hash Trees):** Used in Anti-Entropy (fixing broken replicas). Replicas build a tree of hashes of their data. Instead of sending 1TB of data to see what's different, they compare root hashes. If different, they traverse down the tree to find the exact 1KB block that is out of sync.

---

## 12.9 Security & Reliability
**Keeping it Safe and Standing**

### Auth & JWT
- **OAuth 2.0:** Delegation protocol (Log in with Google).
- **JWT (JSON Web Tokens):** For API auth. Three parts: Header, Payload, Signature. They are mathematically signed by the server's private key. The server DOES NOT need to check the database to verify a JWT; it just verifies the signature curve. Completely stateless auth.

### Rate Limiting
Prevents DDoS and API abuse (e.g., "5 requests per second per IP").
- **Token Bucket:** Bucket fills with tokens at X rate. Requests cost 1 token. Handles burst traffic well.
- **Leaky Bucket:** Requests enter a queue and are processed at a strict, constant rate. Good for smoothing traffic.
- **Sliding Window Log:** Tracks timestamps of every request in Redis. Extremely accurate but memory intensive.

### Circuit Breakers
If Microservice A calls Microservice B, and B is dying/timing-out, A will exhaust all its threads waiting for B, causing A to die too (Cascading Failure).
- **Circuit Breaker Pattern:** If B fails 10 times in a row, the circuit "Trips" (opens). A stops calling B entirely and immediately returns an error to the user for 60 seconds. Then it tries a "half-open" request to see if B recovered.

---

## 12.10 Mock Design: URL Shortener (TinyURL)
**A Classic Read-Heavy Architecture**

**Requirements:** Shorten URL, Redirect Short to Long, Highly Available, 100M URLs generated per day. Read:Write ratio is 10:1.

**1. Hash Generation (The Core Problem):**
- **Base62:** (A-Z, a-z, 0-9). 62 characters.
- A 7-character string gives `62^7 = 3.5 Trillion` combinations (plenty for 10 years).
- **Collision Management:** If two users shorten different URLs, how do we guarantee unique hashes without DB collisions?
- **Solution - Ticket Server (Snowflake):** Do not hash the long URL. Instead, use a centralized Ticket Server (or Twitter Snowflake) to generate a globally unique, auto-incrementing integer (e.g., `100,250,111`). Convert that integer to Base62. Guaranteed unique, zero collisions.

**2. Architecture:**
- Client → Load Balancer → App Servers.
- App Servers talk to a Highly Available NoSQL DB (DynamoDB or Cassandra) because the read volume is massive (1 Billion reads/day), and relationships don't exist.
- Wraparound the DB with **Redis**. Cache the `short_hash -> long_url`. A 10:1 Read ratio means a 90% Cache hit rate easily.

---

## 12.11 Mock Design: News Feed (Twitter)
**The Fanout Architecture**

**Requirements:** Post tweets, View home feed of everyone you follow. Fast loading.

**1. The Fanout Problem:**
When User A requests their feed, we *could* query the DB: `SELECT * FROM tweets WHERE user_id IN (SELECT following_id FROM follows WHERE user_id = A) ORDER BY date`. 
*Result:* At scale, this relational join takes 10 seconds. Unacceptable. We must pre-compute feeds.

**2. Fanout-On-Write (Push):**
- When User A posts a tweet, the server immediately pushes the tweet into the pre-computed Redis Feed Cache of *every person who follows A*.
- *Read time:* O(1). Blazing fast.
- *Problem:* Justin Bieber has 100M followers. One tweet triggers 100M Redis writes. (The "Hotkey / Celebrity" problem).

**3. Fanout-On-Read (Pull):**
- Generate feeds on the fly when the user opens the app.
- *Problem:* Slow for average users.

**4. The Hybrid Solution:**
- Use **Push** for average users (< 100k followers).
- Use **Pull** for celebrities. 
- When I load my feed, the App Server pulls my pre-computed Push feed, checks if I follow any celebrities, fetches their latest tweets directly, and merges them in memory before returning to me. 

---

## 12.12 Mock Design: Chat System (WhatsApp)
**Persistent Connections and State**

**Requirements:** 1-to-1 chat, group chat, online presence, message delivery guarantees.

**1. Connection Protocols:**
- HTTP is useless here (Server cannot push to client).
- Use **WebSockets** for persistent, bidirectional connections between Client and Chat Servers.

**2. Routing Architecture:**
- Bob and Alice open the app. The Load Balancer assigns Bob to ChatServer-1 and Alice to ChatServer-5.
- Bob wants to message Alice. Bob sends msg to CS-1. 
- CS-1 asks a **Redis Routing Cache**: "Which server is Alice connected to?" -> "CS-5".
- CS-1 forwards the message over internal RPC to CS-5. CS-5 pushes message down the WebSocket to Alice.

**3. Offline Delivery & Sync:**
- If Alice is offline, CS-1 pushes the message into a **Message Queue (Kafka)** or a NoSQL Wide-Column DB (Cassandra).
- When Alice connects later, she sends her `last_sync_timestamp`. The server pulls all messages from Cassandra > `last_sync_timestamp` and pushes them.

**4. Presence Servers:**
- Maintaining online/offline status requires a heartbeat.
- Clients ping the Presence Server every 5 seconds. If the server misses 3 heartbeats (15s), the user is marked offline. 

---

## 12.13 Mock Design: Distributed Key-Value Store
**Building DynamoDB / Cassandra from Scratch**

**Requirements:** `put(key, value)`, `get(key)`. Highly scalable, highly available (AP system).

**1. Data Partitioning:**
- Use **Consistent Hashing** with virtual nodes to distribute keys evenly across an arbitrary number of servers. 

**2. Data Replication:**
- To prevent data loss if a node burns down, replicate data. Walk clockwise around the Hash Ring and save the data to the next `N=3` physically distinct nodes.

**3. Consistency & Quorum:**
- Since data is on 3 nodes, how do we know it's accurate? Use Quorum Consensus: `W + R > N`.
- `N = 3` (Replicas).
- `W = 2` (Write quorum: server must get ACKs from 2 nodes for a successful write).
- `R = 2` (Read quorum: server must read from 2 nodes and use vector clocks/timestamps to resolve conflicts).
- Since W(2) + R(2) > N(3), we guarantee strong consistency. For an AP system, we might set W=1 and R=1 for extreme speed, accepting Eventual Consistency.

**4. Handling Failures:**
- **Write Failures (Hinted Handoff):** If Node A is down during a write, Node B temporarily accepts the write and marks it with a "hint". When A boots back up, B hands it over.
- **Read Failures (Anti-Entropy):** Nodes continuously compare their data using Merkle Trees to resolve missing/corrupted data invisibly in the background.

---

## 12.14 Mock Design: Video Streaming (YouTube / Netflix)
**Heavy Blob Storage and Transcoding**

**1. Upload Flow (Asynchronous DAG):**
- Video files are massive. Uploading directly to App servers blocks HTTP threads.
- Client uploads raw video directly to **Amazon S3 (Blob Storage)** via a pre-signed URL.
- S3 triggers an event into a **Message Queue (Kafka)**.
- **Transcoding Workers** consume the event. They pull the raw video and put it through a Directed Acyclic Graph (DAG) of tasks: Extract Audio, add Watermarks, Transcode to 1080p/720p/480p, slice into HLS segments (.ts chunks).
- Segments are saved back to S3. Metadata saved to Relational DB.

**2. Streaming Flow (CDNs):**
- You CANNOT stream video from centralized app servers. Latency and bandwidth costs would bankrupt the company.
- Use a **CDN (Content Delivery Network)**. Video segments are cached at Edge nodes physically located inside ISPs worldwide.
- Client requests video -> Hits closest CDN node. If cached, streams instantly. If not, CDN pulls from S3 Blob storage, caches it, and streams.

---

## 12.15 Mock Design: Location Service (Uber / Yelp)
**Spatial Data and QuadTrees**

**Requirements:** Given user (Lat, Long), find the 10 closest drivers within 5 miles. Must handle extreme write volume (drivers move every 3 seconds).

**1. The Geometric Problem:**
- `SELECT * FROM drivers WHERE lat BETWEEN X and Y AND long BETWEEN W and Z`. 
- SQL databases are awful at 2D bounding box queries. You cannot easily index two independent columns for a dynamic radius.

**2. Spatial Indexing: Geohashing:**
- Converts a 2D (Lat, Long) into a 1D string (e.g., `9q8yy`). 
- The world is mapped as a grid. Sub-grids add characters to the string.
- *Magic Trick:* Locations that are close together share the same string prefix! To find nearby drivers, you do a standard B-Tree lookup: `WHERE geohash LIKE '9q8y%'`.

**3. Spatial Indexing: QuadTrees:**
- An in-memory Tree where each node is a bounding box. If a box has >50 drivers, it splits into 4 child quadrants (NW, NE, SW, SE).
- Searching for nearby drivers takes `O(log N)` by diving down the tree. Stored entirely in RAM.

**4. Extreme Write Volume Handling:**
- Updating a DB or QuadTree every 3 seconds for 1 Million drivers will melt the server.
- **Solution:** Drivers push location to a **Redis Cache** first. A background worker batches the Redis updates every 30 seconds and writes the bulk update to the spatial database. The "live" view combines the DB data with the Redis volatile data.

---

## 12.16 Mock Design: Distributed Rate Limiter
**API Protection at Scale**

**Requirements:** Limit users to 10 API requests per second across a cluster of 50 API Gateways.

**1. The Algorithm:**
- **Sliding Window Log:** Best accuracy. Store a Redis Sorted Set per UserID. The score is the Unix timestamp.
- On Request: Remove all elements older than `now - 1 second`. If `Count(Set) < 10`, accept request & add timestamp. Else, reject (HTTP 429).
- *Trade-off:* Perfectly accurate, but consumes heavy memory.

**2. The Concurrency Problem:**
- If 5 requests hit 5 API Gateways at the exact same millisecond, standard Redis `GET` and `SET` leads to race conditions.
- **Solution:** Wrap the logic in a **Redis Lua Script**. Redis executes Lua scripts atomically (no other commands can interrupt it). This guarantees accurate counting across 50 gateways without distributed locks.

---

## 12.17 Mock Design: Ticketmaster / Hotel Booking
**High Concurrency & Data Integrity**

**Requirements:** Users searching for concert tickets. Ensuring two users cannot book the exact same seat simultaneously.

**1. The Double-Booking Problem:**
- Relational DBs are mandatory here (ACID). NoSQL is strictly forbidden for financial atomic operations.
- User A and B both click "Buy Seat 12". 
- DB `SELECT status FROM seats WHERE id=12` returns "Available" to both.
- Both execute `UPDATE seats SET status=booked`. Double booking occurs.

**2. Pessimistic Locking:**
- User A clicks buy. Backend runs `SELECT * FROM seats WHERE id=12 FOR UPDATE`.
- This locks the row at the SQL engine level. 
- User B's query completely hangs until A's transaction finishes. 
- *Problem:* Severe performance bottlenecks and potential deadlocks.

**3. Optimistic Locking (The Standard Solution):**
- Add a `version` column to the table.
- User A and B read `version = 1`.
- A updates: `UPDATE ... WHERE id=12 AND version=1`. Succeeds. DB increments version to 2.
- B updates: `UPDATE ... WHERE id=12 AND version=1`. Fails! (0 rows affected). App tells B "Seat taken".

**4. The 5-Minute Hold (Distributed Locks):**
- When User A selects a seat, you hold it for 5 minutes during checkout.
- Use **Redis SETNX** (Set if Not Exists) with a TTL of 300 seconds. 
- Key: `seat_12_lock`, Value: `User_A`.
- If B tries to lock, Redis rejects it. If A closes page, TTL naturally releases the lock without deadlocks.

---

## 12.18 Mock Design: Web Crawler
**Massive Distributed Graphs**

**1. Core Architecture:**
- **URL Frontier:** A massive priority queue of URLs to download. Politeness and Priority are managed here.
- **HTML Fetchers:** Distributed workers pulling from the Frontier.
- **DNS Resolver:** Caching DNS lookups locally is mandatory, otherwise DNS requests will bottleneck the entire crawler.
- **Content Extractor:** Parses HTML, extracts links, adds them back to the Frontier.

**2. Cycle & Duplicate Detection:**
- How do we know we haven't already processed `www.apple.com/mac` out of 10 Billion URLs?
- Storing 10 Billion strings in RAM is impossible. Checking a DB every time is too slow.
- **Solution - Bloom Filter:** A probabilistic data structure. Very memory efficient. 
  - `Is it here? -> "Definitely NOT" or "Probably YES"`.
  - If "Definitely NOT", add to frontier. If "Probably Yes", do the expensive DB check.

---

## 12.19 Object-Oriented Design (OOD)
**Code-Level Architecture**

Often asked as a bridge between Algorithms and Systems (e.g., "Design a Parking Lot"). Tests OOP logic.

### The SOLID Principles
1. **Single Responsibility:** A class should have one job. (Don't put DB logic inside your `User` model).
2. **Open/Closed:** Classes are open for extension (inheritance), closed for modification (don't rewrite the core class to add a feature, extend it).
3. **Liskov Substitution:** Derived classes must be perfectly substitutable for their base classes.
4. **Interface Segregation:** Better to have many small interfaces (`IFlyable`, `ISwimmable`) than one giant interface (`IAnimal`).
5. **Dependency Inversion:** Depend on abstractions. Instead of instantiating `SqlDb` directly, inject `IDatabase` into the constructor.

### Standard Patterns
- **Singleton:** Shared resource (e.g., Database Connection Pool).
- **Factory:** Decouples object creation from application logic.
- **Strategy:** Make algorithms interchangeable at runtime (e.g., swapping a `MergeSort` class for `QuickSort` without changing the main app).

---

## 12.20 The MAANG Q&A Bank
**Rapid-Fire Trade-offs & Architecture Decisions**

These are the most common follow-up/push-back questions you will face. Your ability to answer these determines if you get L4 vs L5.

**Q1. "Your database is getting hammered with reads. How do you scale it?"**
*Answer:* Introduce a **caching layer** (Redis) using Cache-Aside. If reads are still too high, implement **Read Replicas** (Master-Slave), routing `SELECT` statements to replicas and `INSERT/UPDATE` to the Master.

**Q2. "What if your caching server (Redis) crashes?"**
*Answer:* If using a single instance, traffic falls back to the DB, causing a **Thunder Herd stampede** and crashing the DB. To prevent this, deploy a **Redis Cluster** across multiple AZs utilizing Consistent Hashing.

**Q3. "We need to scale writes, not just reads. What do we do?"**
*Answer:* Read replicas don't help writes. I must **Shard (Partition)** the database horizontally. Split data logically via a Hash Key. If one Shard gets too hot, use consistent hashing to dynamically spin up new shards.

**Q4. "How do you handle a massive 'Hot Key' bringing down a Redis server?"**
*(Context: A celebrity tweets, 50 million people request the exact same cache node).*
*Answer:* A single server's Network Interface Card (NIC) will saturate. I would add a **Local Cache** (like Guava/LRU cache in memory) directly onto the Web Application servers for strictly viral keys, bypassing the Redis network hop entirely. Alternatively, prepend random integers to the cache key to duplicate it across multiple Redis nodes.

**Q5. "Why would you choose Cassandra over PostgreSQL for this?"**
*Answer:* PostgreSQL (ACID / CP system) is required for strict joins and financial transactions. But for a massive logging system or Chat History, we write billions of rows a day without needing complex relations. Cassandra (Wide-column NoSQL / AP system) offers **insane write-throughput** and peer-to-peer High Availability.

**Q6. "How do you guarantee a notification/payment is sent EXACTLY once?"**
*Answer:* "Exactly-once" delivery over a network is a mathematical myth. You can only guarantee **"At-least-once"**. Therefore, I must make the receiving system **Idempotent**. The client generates an `Idempotency-Key` (UUID) for the payment. The server checks the DB for this key; if it exists, it ignores the duplicate request. If not, it processes the charge and saves the key.

**Q7. "What happens if our Message Queue (Kafka) gets backed up?"**
*Answer:* Scale up the number of consumer worker instances. However, in Kafka, a single Partition can only be consumed by one worker in a group. I must ensure I arbitrarily increase the number of **Kafka Partitions** alongside scaling the workers. Also, set up observability alerts (PagerDuty) for queue depth thresholds.

**Q8. "How do you ensure global users get low latency?"**
*Answer:* Push all static assets (React bundles, images, video segments) to a **CDN** to be served from Edge nodes physically close to the user. For dynamic API calls, deploy stateless app servers in multiple geographic regions (AWS US-East, EU-West, AP-South) and use **Geo-Routing** at the DNS/Load Balancer level.

---

## 12.21 Final Recap

**System Design is about surviving trade-offs:**
- SQL guarantees consistency but scales poorly horizontally.
- NoSQL scales infinitely horizontally but gives up complex relationships.
- Push models make reads fast but writes heavy.
- Pull models make writes fast but reads slow.
- Microservices grant massive isolation but introduce nightmarish network complexity & latency.

*Speak your trade-offs continuously during the interview. Your ability to justify why you DID NOT pick a technology is just as important as why you DID.*

---
*End of roadmap. You have completed the ultimate MAANG preparation guide.*
