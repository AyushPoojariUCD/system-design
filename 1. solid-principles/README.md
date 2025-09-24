# SOLID Principles

--- 

The SOLID principles are a set of five design principles in object-oriented programming (OOP) that make software designs more understandable, flexible, and maintainable. They were introduced by Robert C. Martin (Uncle Bob).

---

## 🔹 1. Single Responsibility Principle (SRP)

Definition:
A class should have only one reason to change, meaning it should only have one responsibility.

✅ Keeps code clean and focused.

✅ Easier to test and maintain.

Bad Example:

```

class Report {
    void generateReport() { /* logic */ }
    void printReport() { /* logic */ }
    void saveToDatabase() { /* logic */ }
}

```

❌ Report is doing multiple things: generating, printing, and saving.

Good Example:

```
class ReportGenerator {
    void generateReport() { /* logic */ }
}

class ReportPrinter {
    void printReport() { /* logic */ }
}

class ReportRepository {
    void saveToDatabase() { /* logic */ }
}
```

✅ Each class has one responsibility.

UML Insight:

Break big classes into smaller cohesive units.

Each unit maps to a single responsibility.

## 🔹 2. Open/Closed Principle (OCP)

Definition:
Software entities (classes, modules, functions) should be open for extension but closed for modification.

✅ Add new functionality without changing existing code.

✅ Encourages polymorphism and abstraction.

Bad Example:

```
class AreaCalculator {
    double calculate(Object shape) {
        if (shape instanceof Circle) {
            return Math.PI * ((Circle) shape).radius * ((Circle) shape).radius;
        } else if (shape instanceof Square) {
            return ((Square) shape).side * ((Square) shape).side;
        }
        return 0;
    }
}
```

❌ Adding a new shape requires modifying AreaCalculator.

Good Example:
```
interface Shape {
    double area();
}

class Circle implements Shape {
    double radius;
    public double area() { return Math.PI * radius * radius; }
}

class Square implements Shape {
    double side;
    public double area() { return side * side; }
}

class AreaCalculator {
    double calculate(Shape shape) {
        return shape.area();
    }
}
```

✅ Adding a new shape only requires extending Shape, not modifying AreaCalculator.

UML Insight:

Use interfaces/abstract classes to allow extension.

## 🔹 3. Liskov Substitution Principle (LSP)

Definition:
Objects of a superclass should be replaceable with objects of its subclasses without breaking the application.

✅ Subclasses should behave like their parent.

✅ Prevents unexpected runtime errors.

Bad Example:

```
class Bird {
    void fly() { /* logic */ }
}

class Ostrich extends Bird {
    void fly() { throw new UnsupportedOperationException(); }
}
```
❌ Ostrich cannot fly, breaking substitution.

Good Example:
```
interface Bird { }

interface Flyable {
    void fly();
}

class Sparrow implements Bird, Flyable {
    public void fly() { /* logic */ }
}

class Ostrich implements Bird {
    // no fly method, still valid
}
```

✅ Subtypes respect parent expectations.

UML Insight:

Avoid “wrong inheritance”.

Separate capabilities into interfaces.

## 🔹 4. Interface Segregation Principle (ISP)

Definition:
Clients should not be forced to depend on interfaces they do not use.

✅ Break large interfaces into smaller, role-specific interfaces.

✅ Improves modularity.

Bad Example:
```
interface Worker {
    void work();
    void eat();
}

class Robot implements Worker {
    public void work() { /* logic */ }
    public void eat() { /* not applicable */ }
}
```

❌ Robots don’t eat, but still must implement eat().

Good Example:
```
interface Workable {
    void work();
}

interface Eatable {
    void eat();
}

class Human implements Workable, Eatable {
    public void work() { /* logic */ }
    public void eat() { /* logic */ }
}

class Robot implements Workable {
    public void work() { /* logic */ }
}
```

✅ Interfaces are split, and each class implements only what it needs.

UML Insight:

Favor multiple small interfaces over one large interface.

## 🔹 5. Dependency Inversion Principle (DIP)

Definition:
High-level modules should not depend on low-level modules. Both should depend on abstractions.

✅ Reduce coupling between components.

✅ Easy to swap implementations.

Bad Example:
```
class MySQLDatabase {
    void connect() { /* logic */ }
}

class Application {
    private MySQLDatabase db = new MySQLDatabase();
    void start() { db.connect(); }
}
```

❌ Application depends on a specific database.

Good Example:
```
interface Database {
    void connect();
}

class MySQLDatabase implements Database {
    public void connect() { /* logic */ }
}

class PostgreSQLDatabase implements Database {
    public void connect() { /* logic */ }
}

class Application {
    private Database db;
    public Application(Database db) {
        this.db = db;
    }
    void start() { db.connect(); }
}
```

✅ Application depends on the abstraction Database.

UML Insight:

Depend on interfaces, not concrete classes.

✅ Benefits of SOLID

Clean, modular, and extensible code

Reduced coupling, increased cohesion

Easier testing and maintenance

Better scalability

## 📊 UML Cheat Sheet (Visual Summary)

```
+--------------------------+
|        SRP               |
| One class = One job      |
+--------------------------+

+--------------------------+
|        OCP               |
| Extend, don’t modify     |
+--------------------------+

+--------------------------+
|        LSP               |
| Subtypes must behave     |
| like base types          |
+--------------------------+

+--------------------------+
|        ISP               |
| Many small interfaces    |
| > one large interface    |
+--------------------------+

+--------------------------+
|        DIP               |
| Depend on abstractions   |
| not concrete classes     |
+--------------------------+
```

---

## 📌 Conclusion:
Following SOLID principles ensures that your code is scalable, maintainable, and adaptable to future changes. They form the foundation of clean software architecture.

---
