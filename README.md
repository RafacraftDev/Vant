![Vant_logo](https://github.com/RafacraftDev/Vant/blob/main/Vant_logo2.png?raw=true)

# 💎 About Vant
​Vant is a custom programming language I created because I wanted a syntax that felt more "right" than C++ (ironically, the engine behind many languages). Vant scripts use the `.vant` extension.
​The base syntax is a hybrid: it takes the structure and braces `{}` of Java/C#, the clean variable handling of Kotlin, and the simplicity of functions and comparisons from Python.

# ⚠️ Before using Vant (The Reality Check)
Vant is a passion project developed in my free time between school, other coding experiments, and my [Youtube channel](https://youtube.com/@rafacraftcoder?si=8IM1v9t_agLFbkBq) Because of that, you should keep in mind:
- Documentation: Non-existent. You are the pioneer here.
- Stability: Most errors will simply crash the interpreter without warning. It's not a bug, it's a "surprise exit".
- Performance: It's an interpreter, not a rocket. It's built for learning and fun, not for mining Bitcoin.

Initially, Vant was designed to be the bare minimum needed to create functional logic with a safe-guard twist (like the safe / failed blocks). It’s a work in progress that will likely evolve as long as I find it interesting to code.

# 🚀 Quick comparison
| Feature | Python | Java | Vant |
| :--- | :--- | :--- | :--- |
| Variable | x = 10 | int x = 10 | var x = 10; |
| Input | input() | Scanner | input() |
| Strings | "hi" == "hi" | "hi".equals("hi") | "hi" == "hi" |
| Safety | try/except | try/catch | safe/failed |

# Here is some example code:
```scala
class Main {
  @static
  def main() {
    // variables types "var|val|obj";
    var x = 10;
    val y = 20;
    obj z = 30;
    var result = x + y + ((integer) z);

    if (result == 60) {
      printl("result == 60");
    } elif {
      printl("result != 60, is ${result}");
    }
  }
}
Main.main();
```
