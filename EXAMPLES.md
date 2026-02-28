<img width="1280" height="720" alt="1000253733" src="https://github.com/user-attachments/assets/fe511944-93b6-41e8-ad2b-ebdf6e850798" />

# Examples
Here's an example of the Vant engine
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

Example of how to use the keyboard keys
```scala
import { Key } from "@vant/Key";

forever(() => {
  if (Key.inDown(Key.SPACE)) {
    printl("SPACE pressed!");
  }
});
```

Example code for creating a game
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
    
    construct( pass: string, gmail: string, user: string) : Error : Async : {
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
        } if (User.exists(user) == false) {
            User.add(user);
            self.username = user;
        } else {
            Error.put("this name is used");
        }
    }
    def createAccount( pass: string, gmail: string, user: string) {
        return User(pass,gmail,user);
}

safe {
    User pablo = createAccount(
        "12345",
        "pablojuarez62@gmail.com",
        "pablo juarez"
    );
} failed (e) {
    e.printErr();
}
```
