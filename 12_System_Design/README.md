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
| [12.7](#127-core-concepts--cap-theorem) | Core Concepts: The CAP Theorem | 5 min |
| [12.8](#128-mock-design--url-shortener) | Mock Design: URL Shortener (TinyURL) | 15 min |
| [12.9](#129-mock-design--news-feed) | Mock Design: Twitter / News Feed | 15 min |
| [12.10](#1210-mock-design--chat-system) | Mock Design: Chat System (WhatsApp / Discord) | 15 min |
| [12.11](#1211-object-oriented-design) | Object-Oriented Design (OOD) & SOLID | 15 min |
| [12.12](#1212-recap) | Final Recap | 5 min |

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

## 12.7 Core Concepts: The CAP Theorem
**Distributed Data Trade-offs · 5 min**

In any distributed data store, you can only guarantee **two out of three**:
1. **Consistency (C):** All nodes see the same data at the same time.
2. **Availability (A):** Every request receives a response (even if it's stale data).
3. **Partition Tolerance (P):** The system operates despite network failures between nodes.

**Real-World Application:** Networks fail, so **P is mandatory**. You must choose between **CP** (Banking systems — better to fail a request than show wrong balance) and **AP** (Social Media — better to show a slightly outdated post count than crash the site).

---

## 12.8 Mock Design: URL Shortener
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

## 12.9 Mock Design: News Feed
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

## 12.10 Mock Design: Chat System
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

## 12.11 Object-Oriented Design
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

## 12.12 Recap

**System Design is about surviving trade-offs:**
- SQL guarantees consistency but scales poorly horizontally.
- NoSQL scales infinitely horizontally but gives up complex relationships.
- Push models make reads fast but writes heavy.
- Pull models make writes fast but reads slow.

*Speak your trade-offs continuously during the interview. That is the true test of a senior engineer.*

---
*End of roadmap. You have completed the ultimate MAANG preparation guide.*
