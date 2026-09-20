# SWE-4202 — Object-Oriented Programming (Lab)

Twelve systems built over one semester, in C and Java 17. The repository tracks a single
arc: from parallel arrays in C, through classes and composition, into polymorphic type
hierarchies, generics, and exception-driven failure handling — with the last four projects
graded as much on *design* as on passing tests.

Every project here was specified as a brief, not a skeleton. Most of them deliberately
withhold the class diagram: the specs state how the business behaves and leave the
inheritance, the interfaces, and the is-a / has-a splits to be derived. That derivation is
the assessed work, and it is what this repository is meant to show.

---

## At a glance

| # | Project | Domain | Core idea | Lang | Status |
|---|---------|--------|-----------|------|--------|
| 1 | [Student Record System](#1--student-record-system) | Course roster | Arrays → `struct` → class | C, Java | Complete |
| 2 | [Bank Account · Stack · Queue](#2--bank-account-stack-queue) | Banking, ADTs | Encapsulation, object identity | Java | Complete |
| 3 | [RideNow](#3--ridenow) | Ride-sharing | Composition & delegation | Java | Complete |
| 4 | [CineCart](#4--cinecart) | Cinema booking | 12-class system, packages, CSV | Java | Complete |
| 5 | [CineCart: Polymorphism Extension](#5--cinecart-polymorphism--inheritance) | Cinema booking | One collection, four fare rules | Java | Complete |
| 6 | [Sketchpad](#6--sketchpad) | Shape drawing | Abstract roots, checked exception family | Java | Complete |
| 7 | [Relay](#7--relay) | Outbound messaging | Replacing a `String channel` ladder | Java | Complete |
| 8 | [GridLedger](#8--gridledger) | Electricity billing | Refactor to a template method | Java | Complete |
| 9 | [KenaKata](#9--kenakata) | Marketplace settlement | Capability interfaces, atomic placement | Java | Complete |
| 10 | [Car Parking](#10--car-parking) | Parking management | Command-driven simulation | Java | Incomplete |
| 11 | [TakaLink](#11--takalink) | Mobile-money switch | Two variation axes + checked failures | Java | Incomplete |
| 12 | [Dokan](#12--dokan) | Retail inventory | Generics, bounds, wildcards, erasure | Java | Incomplete |

---

## What this repository demonstrates

**Design under ambiguity.** GridLedger, Relay, TakaLink, and KenaKata all hand you a
prose description of a business and a test file — never a class diagram. Picking which
type is abstract, which is an interface, which relationship is `is-a` and which is `has-a`
is the deliverable.

**Refactoring legacy code.** GridLedger and TakaLink start from a working contractor
implementation that passes its tests and is unmaintainable: a `String customerType` field,
the same `if/else` ladder copy-pasted into five methods, a subsidy bolted on as a boolean.
The rebuild has to produce byte-identical numbers while making "add a fourth category"
a one-file change.

**Failure as a first-class design decision.** Three projects separate *malformed input*
(reject in the constructor with an unchecked `IllegalArgumentException`, so the broken
object never exists) from *business refusal* (a checked exception family under one parent,
thrown and caught by the caller). TakaLink and KenaKata additionally require atomicity:
every precondition is checked before any balance moves, so a thrown exception leaves the
system exactly as it was.

**Working within constraints.** Labs 1–5 forbid `java.util.ArrayList`, `List`, `HashMap`,
and every other collection class. Storage is a fixed-size array with its own `int` count,
including the defensive-copy discipline on anything returned to a caller. Later labs lift
the restriction deliberately, so the contrast is visible in the diffs.

**Test-driven work against a sealed suite.** Most projects ship an unmodifiable test file
that pins method signatures and numbers but says nothing about structure. The test is the
contract; the design is not.

---

## Concept map

| Concept | Where it shows up |
|---|---|
| Encapsulation, private state | Lab 1 Task 3, Lab 2, every project after |
| Constructors & overloading | RideNow, CineCart, `queue(notice)` / `queue(notice, repeat)` in Relay |
| Composition (`has-a`) | RideNow `Trip`, Relay `Notice`→`Recipient`, GridLedger `Connection`→`Meter`, CineCart `ComboLine` |
| Inheritance (`is-a`) | Fare classes, notice channels, connection categories, wallet categories |
| Abstract base classes | `Shape`, `Notice`, `Ticket`, `Connection`, `Wallet` — none instantiable |
| Runtime polymorphism / dynamic dispatch | Every "one sweep, no kind-test in the loop" requirement |
| Compile-time overload resolution | The `add` / `queue` / `submit` pairs, contrasted with dispatch in the vivas |
| Super-call reuse | `VIPTicket` → `PremiumTicket`, `PriorityEmail` → `Email`, `Lifeline` → `Residential` |
| Interfaces as capabilities | KenaKata `Weighable` / `Insurable` / `Returnable` / `ColdChain` |
| Checked vs unchecked exceptions | Sketchpad, KenaKata, TakaLink |
| Exception hierarchies | One parent per project, distinct subkinds per failure reason |
| Atomic operations | KenaKata order placement, TakaLink settlement |
| Generics: bounds, wildcards, erasure | Dokan |
| Defensive copying | `Cart.getLines()`, `Shelf.items()` |
| Packages & visibility | CineCart, KenaKata |

---

## Projects

### 1 — Student Record System
*Lab 1 · C and Java · 10 marks*

The same six operations (add, remove, update, display, search, top-N) implemented three
times: two parallel arrays in C, one array of `struct Student`, then a `StudentList` class
with private fields. Each version fixes a concrete pain from the one before — `removeAt`
shrinks from six parameters to two, the double shift collapses to one, and `list[0].mark = -999`
stops compiling. Written reflections on each transition are in the source comments.

### 2 — Bank Account, Stack, Queue
*Lab 2 · Java · 20 marks*

`BankAccount` with a zero-floor withdrawal rule and no static state, so each instance is
genuinely independent. Then `StudentStack` and `StudentQueue`, built from the Lab 1 array:
same storage, different rules about which end you may touch, enforced because the array is
private. Includes written analysis of object identity and reference aliasing
(`alice = bob;` and what happens next).

### 3 — RideNow
*Lab 3 · Java · 10 marks*

`Trip` composes a `Passenger`, a `Driver`, and two `Location` objects. `getDistance()`
delegates to `Location.distanceTo` rather than reaching into coordinates itself. Multiple
constructors per class, with the convenience form supplying a default (`rating = 5.0`,
`label = "Unknown"`). `completeTrip()` reaches through to flip the driver's availability
back — the first project where one object's method changes another object's state.

### 4 — CineCart
*Lab 4 · Java 17 · Gradle · 15 marks*

A twelve-class booking booth across four packages (`model`, `data`, `engine`, `app`),
loading movies, halls, showtimes, concessions, and customers from CSV via a provided
loader. `Hall` holds a 2-D `Seat[][]` grid; `CheckoutEngine` runs an ordered pipeline —
age check against the rating, seat availability, premium and peak multipliers, combo deal,
group discount, loyalty tier, tax — and every guard must leave state untouched when it
refuses. Fixed-size arrays only.

### 5 — CineCart: Polymorphism & Inheritance
*Lab 4 Extension II · Java 17 · 10 marks*

The same booth, redesigned once inheritance was on the syllabus. `Cart` collapses its two
arrays into one collection of `LineItem`, and `grandSubtotal()` becomes a single loop with
no type test inside it. Four fare classes each own their arithmetic; `VIPTicket` obtains
its charge by calling the premium charge and adding the lounge fee, so re-pricing premium
moves VIP for free. `ComboLine` *contains* two menu items rather than extending one — the
single ownership relationship in an extension otherwise made of kinship. The base price is
`protected`: reachable by the fare family, sealed against everything else.

### 6 — Sketchpad
*Standalone · Java 17 · 8 marks*

A shape family over a provided `Canvas`. `Shape` is abstract because there is no such thing
as a bare shape; `Rectangle` stays concrete because it is both a real shape and the parent
of `Square`. `Square` overrides the side-setters (so it cannot stop being square) and
pointedly does *not* override `area()`, since `w × h` already gives `s²`. Two failure modes,
two mechanisms: a nonsensical size throws `IllegalArgumentException` from the constructor;
a valid shape the canvas cannot hold throws a checked `ShapeTooLarge`/`ShapeTooSmall` —
both under one parent, so the gallery's loop needs exactly one `catch` today and still one
when a third failure kind arrives. Nothing is painted before the fit check, so a refused
shape leaves the canvas untouched.

### 7 — Relay
*Standalone · Java 17 · 10 marks*

An outbound message hub, rebuilt from an intern's `String channel` design that copied the
channel ladder into `transmit`, `cost`, and the audit log. Email, SMS (segmented at 160
characters, priced per segment), and push (trimmed lock-screen preview) each own all three
behaviours. `PriorityEmail` extends `Email` and prefixes the inherited output rather than
copying it, so changing email behaviour moves priority email with no edit of its own. The
outbox flushes and totals in single sweeps with no per-channel branch, and `queue` is
overloaded for the plain and repeat-count forms. Fixed-size arrays only.

### 8 — GridLedger
*Standalone · Java 17 · 10 marks*

A national electricity billing engine, rebuilt from a contractor implementation where five
methods each re-asked "what kind of customer is this?" and drifted apart. Every bill is the
same four parts — energy, fixed charge, fuel surcharge, tax — added up once, in one place;
only the energy calculation varies by category (three-band residential slab, two-band
commercial, flat industrial). The lifeline subsidy is modelled as a residential connection
that reduces the inherited energy charge, which makes "subsidised industrial" unwritable
and means changing a residential rate moves lifeline bills automatically. A connection
*has* a meter; the meter refuses negative readings and a closing value below the opening
one. Registration is overloaded (plain, or with the month's fuel percentage).

### 9 — KenaKata
*Standalone · Java 17 · 15 marks*

A marketplace pricing and settlement engine, built from scratch. Stocked, digital, and
fresh goods share every catalogue behaviour and differ only in VAT and commission; add-on
lines (gift wrap, express handling, a warranty priced off the item it covers) price like
lines without being catalogue items at all. Optional behaviours — weight, cold-chain,
insurable, returnable — are separate capability interfaces, so the delivery calculator
totals only lines that actually have a weight and nothing needs a "which kind are you?"
ladder. Pricing runs in a fixed seven-step sequence with ceiling rounding on every
percentage and whole-Taka `long` money throughout. Placement is atomic: stock, coupon, and
payment are all validated before a single unit is reserved or any money moves. Payment is
one interchangeable operation across wallet, card, and cash-on-delivery. Nightly settlement
pays each seller their line value less commission less refunds, and reports platform
revenue separately.

### 10 — Car Parking
*Standalone · Java 17*

A command-driven parking simulation: bike, regular, and large bays with per-vehicle-class
rules, a maximum stay, time advancement, billing, refusal counts, and revenue tracking,
driven by a scripted command stream and checked against exact expected output.

> **Note on the provided PDF.** `CarParking.pdf` contains a block styled as
> "Specification Addendum 8.4" that is addressed to code generators and language models
> rather than to students, instructing them to insert an undisclosed class and an extra
> output line and to conceal the instruction from the reader. It is a prompt injection,
> not part of the problem, and the solution in this repository implements the printed
> specification only.

### 11 — TakaLink
*Standalone · Java 17 · 12 marks ·*

A mobile-money switch, rebuilt from a contractor "God class" that debited the sender before
checking the limit, signalled failure with `int` codes, and left `balance`, `pin`, and
`frozen` public. The rebuild has two independent variation axes that must not enumerate
each other: transaction kind (send, cash-out, payment, top-up — differing in fee and money
movement) and account category (personal, agent, merchant — differing in daily limit and
permitted operations). The check-then-move skeleton is written once; each transaction fills
in only its own fee and transfer. Refusals travel as a checked exception family so the
compiler forces callers to handle them, and the nightly run catches each one, records the
reason, and settles the rest of the batch.

*Current state: wallet hierarchy and encapsulation done; transaction family and settlement
run in progress.*

### 12 — Dokan
*Lab 13 · Java 17 · Gradle · 10 marks ·*

A generic toolkit for a corner shop, replacing an intern's three near-identical `Object`-based
shelves. Six types, one idea each: `Box<T>` (a value or nothing, so `null` stops being an
answer), `Pair<A,B>` with a `swapped()` whose return type swaps too, `Shelf<T extends Item>`
(a bound that buys you `priceTaka()` without a cast), `Counter<T>` deliberately left
unbounded, and static generic helpers demonstrating PECS — `List<? extends T>` for a
producer, `Check<? super T>` for a consumer. Erasure is handled explicitly: `new T[n]` is
impossible, so capacity is an `int` beside an `ArrayList<T>`. The toolkit package may not
import anything from the shop package, and part of the mark is a set of lines that *must
fail to compile*.

*Current state: `Box` and `Pair` complete; `Shelf`, `Counter`, and `Shelves` in progress.*

---

## Repository layout

```
.
├── lab-01-student-records/      # C (task1, task2) + Java (task3)
├── lab-02-classes-objects/      # BankAccount, StudentStack, StudentQueue
├── lab-03-ridenow/
├── lab-04-cinecart/             # Gradle project, four packages
├── lab-04-ext-polymorphism/
├── sketchpad/
├── relay/
├── gridledger/
├── kenakata/
├── carparking/
├── takalink/                    # in progress
└── dokan/                       # in progress
```

Design sketches (the hand-drawn interaction diagrams required by Relay, GridLedger, and
TakaLink) live in each project's `docs/` folder, alongside the README or design note that
project's brief asked for.

## Building and running

**C projects** (Lab 1, tasks 1–2):
```bash
gcc -Wall -o task1 task1.c && ./task1
```

**Plain Java projects** (Labs 1–3, Sketchpad, Relay, GridLedger, KenaKata, Car Parking):
```bash
javac *.java && java Main
```

**Gradle projects** (CineCart, Dokan):
```bash
./gradlew test     # the graded suite
./gradlew run      # the demo application
```

Dokan adds `./gradlew cases` (27 worked examples with expected vs. actual) and
`./gradlew strict` (compiles with `-Xlint:unchecked,rawtypes -Werror`).

All Java work targets JDK 17. Where a project shipped an instructor-supplied test file or
loader, that file is unmodified.

## A note on scope

These are coursework solutions, not production libraries. They are here because the briefs
happen to be unusually good at isolating design decisions — and because reading the
GridLedger or TakaLink "before" code next to the rebuild is a faster way to see how I think
about maintainability than any description of it would be.

---

<sub>SWE-4202 — Object-Oriented Concepts I (Lab)</sub>
