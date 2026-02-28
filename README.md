<img width="1280" height="720" alt="1000253733" src="https://github.com/user-attachments/assets/6f46496c-5733-44a7-aedf-180a8810e65a" />


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
    } else {
      printl("result != 60, is ${result}");
    }
  }
}
Main.main();
```

key example
```scala
import { Key } from "@vant/Key";

forever(() => {
  if (Key.inDown(Key.SPACE)) {
    printl("SPACE pressed!");
  }
});
```

game example
```scala
import { Key } from "@vant/Key";
import { Visual, Graphics } from "@vant/Visual";

class Game {
    // We initialize the Visual objects
    var player = Visual();
    var enemy = Visual(); 
    var dirt = Visual();
    
    var jumpTime = 0;
    var jumpTimeMax = 50;
    
    @static
    def main() {
        // Asset load
        dirt.texture = "./dirt.png";
        player.texture = "./player.png";
        enemy.texture = "./enemy.png";
        // type of repeated texture
        dirt.repeatTexture({
            width: 9999,
            height: 5
        });
        // object coordinates 
        dirt.y = -100;
        player.x = 100;
        enemy.x = -100;
        
        (player, enemy, dirt).show();
        // repetition time
        forever(() => {
            Game.update(); 
            // if the key is pressed
            if (Key.inDown(Key.SPACE) && player.touch(dirt)) {
                Game.jumpTime = Game.jumpTimeMax;
            }
            // if the jump time is zero
            if (Game.jumpTime > 0) {
                player.y += 2;
                Game.jumpTime -= 1;
            }
        });
    }
    
    @static
    def update() {
        // player collisions
        if (player.touch(dirt) == false && Game.jumpTime <= 0) {
            player.y -= 1;
        } 
        // collisions of enemy
        if (enemy.touch(dirt) == false) {
            enemy.y -= 1;
        }

        Graphics.update();
    }
}

Game.main();

```

Testing the startup of sections with Google Gmail
```scala
import { Users } from "./users/usersList";
import { Gmail } from "@vant/gmail";

class User {
    var password = string(null);
    var gmail = string(null);
    var username = string(null);
    
    def createAccount( pass: string, gmail: string, user: string) : Error : Async : {
        var getter = Gmail.exists(gmail);
        until(getter.response() == true);
        var existsGmail = getter.getExists();
        if (len(pass) >= 8) {
            self.password = pass.encrypt;
        } else {
            Error.put("password is unsafe");
        } if (existsGmail == true) {
            self.gmail = gmail;
        } else {
            Error.put("doesnt exists gmail");
        } if (User.exists(user)) {
            self.username = user;
        } else {
            Error.put("this name is used");
        }
        exit new User;
    }
}

User pablo = createAccount(
    "12345",
    "pablojuarez62@gmail.com",
    "pablo juarez"
);
```
