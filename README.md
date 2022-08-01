# Cub3D


A [42](https://42.fr/en/homepage/) project inspired by the famous [Wolfeinstein3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) in order to explore how [ray casting](https://en.wikipedia.org/wiki/Ray_casting) works. This project uses the [minilibx](https://github.com/42Paris/minilibx-linux) and works on both linux and Mac OS (until Mojave).

Any map can be supported, feel free to make your own .cub file.

## 🧭 Usage

Clone the repository and access it with `cd`. From there, you can choose between these 2 options :

### **[Bonus mode]** - Play with custom sprites, wall collision, skybox (recommended)
![recording bonus](recording_bonus.gif)

```
make bonus
./cub3D scene/custom.cub
```


### **[Basic mode]** - a simple Wolfenstein 3D look and feel, no collision
![recording basic](recording_basic.gif)

```
make
./cub3D scene/wolf.cub
```

## 🎮 How to play 
Key|Action
---|------
<kbd>W</kbd>|Move forward
<kbd>A</kbd>|Move left
<kbd>S</kbd>|Move right
<kbd>D</kbd>|Move backwards
<kbd>←</kbd>|Pivot left
<kbd>→</kbd>|Pivot right
<kbd>↑</kbd>|Run (hold with <kbd>W</kbd>, <kbd>A</kbd> or <kbd>S</kbd>)

## 📚 Ressources

- [Lodev's raycasting tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Minilibx documentation](https://harm-smits.github.io/42docs/libs/minilibx)
