![Vant_logo](https://github.com/RafacraftDev/Vant/blob/main/Vant_logo2.png?raw=true)

Vant is a modern programming language built for safety and high performance. it ensures a robust and predictable development experience.

# ✨ Key Features
- Unique Variable Management: Full control using var (strict), val (constant), and obj (dynamic).
- Native File Extension: Support for `.vant` files.
- Safety First: An internal engine designed to prevent runtime type errors.
- Clean Syntax: Combines the robustness of Java with a `modern`, streamlined developer experience.

### ❓ Why use it?
It contains a large number of features and secure methods that create a safe way to code on any device, as it has an application for use from Android.

# ​🛠️ Vant Syntaxis
Vant features a robust and safe syntax that uses

### ​Variables & Mutability
​Vant categorizes data storage.

| Type | Mutability | Type Safety | Example |
| :--- | :--- | :--- | :--- |
| **var** | Mutable | Strict (Locked) | `var x = 10` |
| **val** | Immutable | Static | `val PI = 3.14` |
| **obj** | Mutable | Dynamic | `obj data = "hi"` |

### ⭐ Class Structure
​In **Vant**, a class serves as the essential ***blueprint*** for creating instances and objects. These structures encapsulate data and functions designed to interact with the development environment or manage complex data states. By using a ***construct*** block, Vant ensures that every object is properly initialized, maintaining a clean and predictable flow throughout the code.
Example: 
```scala
// Example of a Vant Class
class Player {
    // Properties
    var nickname = "";
    val id = 0;

    // The construct block initializes the object
    construct(name: string, identification: integer) {
        self.nickname = name;
        self.id = identification;
    }
}

```

### 💡 Function use
A function in Vant is an essential blueprint for executing specific tasks or logic. While a class defines the structure of an object, a function defines the actions that occur within the development environment. Functions allow you to reuse code, process data, and trigger events efficiently.
```scala
var status = string(null);
// Function (Method)
def saveData(data: obj) {
    status = data.stringValue();
}

// Global function example
def printStatus(message: string) {
    cout(self.status);
}

```

### 🛡️ Null Safety & Default Values
Vant avoids the `NullPointerException` by automatically converting null types into safe values:

| Conversion | Input | Output (Safe) |
| :--- | :--- | :--- |
| `string(null)` | `null` | `""` (Empty String) |
| `bool(null)` | `null` | `false` |
| `integer(null)` | `null` | `0` |
| `decimal(null)` | `null` | `0.0` |

### ⭐ Vant vs Others Lenguages
Vant combines the readability of dynamic languages with the power of compiled languages.
| Feature | Python | Java | **Vant** |
| :--- | :---: | :---: | :---: |
| Syntax | Simple | Complex | **Simple** |
| Performance | Medium | High | **High** |
| Safety | Dynamic | Strict | **Hybrid (var/obj)** |

### 🛡️ Error Handling: The `safe` Block
Vant uses a native protection structure to prevent unexpected shutdowns.
```swift
safe {
  var x = 0/0;
} failed(e) {
  e.printErr();
}
```

### 📈 Differences with other languages
| Language | Syntax Example | Type System |
| :--- | :--- | :--- |
| **Java** | `int x = 10;` | Static (Explicit) |
| **JavaScript** | `let x = 10;` | Dynamic |
| **Python** | `x = 10` | Dynamic |
| **Vant** | `var x = 10;` | **Strict (Inferred & Locked)** |
