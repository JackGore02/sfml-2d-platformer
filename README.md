# SFML 2D Platformer

A two-level side-scrolling platformer prototype developed collaboratively in C++ with SFML 2.5.1. The project was created for a university group-work assignment and was built on top of a custom game framework supplied by the university.

The player traverses data-driven levels made from static platforms, moving platforms, traps, and a goal object. A horizontally tracking camera follows progress through layered environments, while reaching each goal advances the level flow.

## Project context and my contribution

This was created as a university group-work project by Ash, Jack, Sam, and Josh. The underlying LJMU game framework was supplied with the assignment and was not created by any member of the group. **Dr Chris Carter** is the author of the framework the game was built on top of.

My specific role was **Level Developer**. My work focused on the construction, data, presentation, and runtime behaviour of the two platforming levels, together with implementation that directly overlapped with those areas. This included placing and configuring platforms, moving platforms, traps, goals, backgrounds, and foregrounds, loading level data and assets, implementing the player-following camera and parallax behaviour, resetting the level and camera when the player falls out of the world, and coordinating level-completion state transitions.

I designed each level visually in Adobe Photoshop before transferring it into the game. The layouts were created on images whose dimensions matched the coordinate space the game was designed around. Photoshop's element coordinates were then used to determine the corresponding world positions written into the level and environment data files. This provided a practical visual-authoring workflow for arranging long platforming routes before testing and refining them in the running game.

I also worked closely with the Player Developer on the collision behaviour required by the levels. This overlap covered landing on platforms, colliding with their sides and undersides, avoiding tunnelling during fast vertical movement, trap knockback, moving-platform contact, and detecting interaction with a level goal.

The repository is preserved as a record of the collaborative coursework. Because responsibility for the complete project was shared across the group, unfinished, incomplete, or inconsistent areas outside my development role should not be interpreted as representative of my individual ability or the quality of my independently developed work.

## Features

- Two data-driven side-scrolling levels
- Static platforms with different dimensions and arrangements
- Vertically moving platforms configured through per-object amplitudes
- Trap placement and player knockback integration
- Goal objects that drive level-completion transitions
- Swept platform collision handling for landing, walls, and ceilings
- Layered background, gameplay, and foreground rendering
- Horizontally tracking gameplay camera
- Foreground parallax movement and camera-relative environmental layers
- Player and camera reset after falling outside the playable world
- Level-one to level-two transition and return to the menu after level two

## Controls

| Context | Key | Action |
| --- | --- | --- |
| Level | <kbd>Left</kbd> / <kbd>Right</kbd> | Move across the level |
| Level | <kbd>Space</kbd> | Jump; jump into a goal doorway to complete the level |
| Level | Hold <kbd>Left Shift</kbd> | Sprint |

## Requirements

- Windows 10 or Windows 11
- Visual Studio 2022 with the **Desktop development with C++** workload
- MSVC v143 platform toolset
- Windows 10 SDK
- No separate SFML installation is needed. The required SFML 2.5.1 headers and x64 static libraries are included under `ThirdParty/SFML-2.5.1`.

## Building and running

1. Open `SFML 2D Platformer.sln` in Visual Studio 2022.
2. Select either **Debug** or **Release**. The project targets x64.
3. Choose **Build > Build Solution** or press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
4. Run without the debugger using <kbd>Ctrl</kbd>+<kbd>F5</kbd>.

You can also build from a Visual Studio Developer Command Prompt:

```powershell
msbuild "SFML 2D Platformer.sln" /p:Configuration=Release /p:Platform=x64
```

Build output is written beneath `build/<platform>/<configuration>`. The game loads assets through paths relative to the `SFML 2D Platformer` project directory. Running from Visual Studio provides the intended working directory, use that same directory if launching the executable manually.

## Gameplay

- The player begins each level near its left-hand edge.
- Static platforms form the main route through each approximately 9,500-pixel-wide level.
- Smaller platforms can move vertically using a sinusoidal offset and an amplitude defined in the level data.
- Touching a trap launches the player upwards and pushes them away horizontally.
- The camera remains centred at the start of a level, then follows the player's horizontal position after the player passes half the window width.
- Environmental and foreground layers move at different rates to provide depth while the camera scrolls.
- Falling below the playable world returns the player to the starting position and resets the camera.
- Jumping into the goal doorway at the end of level one loads level two.
- Completing the goal in level two removes the gameplay screen and returns to the underlying menu.

## Relevant project structure

```text
SFML 2D Platformer.sln
|-- SFML 2D Platformer/
|   |-- Source/
|   |   |-- Engine/                         # University-supplied LJMU framework
|   |   `-- Game/
|   |       |-- GameScreenLevel.*           # Level loading, updating, camera, and transitions
|   |       |-- GameDataFiles.h             # Environment and level-geometry parsing
|   |       |-- GameObjectBasic.*           # Platforms, traps, goals, and layered scenery
|   |       |-- GamePlayer.*                # Shared player/level collision integration
|   |       `-- GameCamera.*                # SFML view used by the level camera
|   `-- Assets/
|       |-- Data/
|       |   |-- level_geom.txt              # Level-one platform, trap, and goal data
|       |   |-- level2_geom.txt             # Level-two platform, trap, and goal data
|       |   |-- level_env.txt               # Level-one environmental layers
|       |   `-- level2_env.txt              # Level-two environmental layers
|       |-- Backgrounds/                    # Background and foreground artwork
|       `-- Statics/                        # Platform, trap, and goal textures
`-- docs/                                   # Original framework documentation and archive
```

## How it works

`LJMUGameScreenLevel` owns the active level objects, environmental layers, foreground layers, player, and gameplay camera. When the screen loads, it selects the resource lists and data files for the current level. `SideEnvMgr` describes each visual layer, while `SideLevelMgr` reads every gameplay element's texture reference, position, movable flag, movement amplitude, trap flag, and goal flag. The level screen converts those records into `GameObjectBasic` instances.

The source coordinates in those data files were produced from the Photoshop level layouts. Each platform, trap, goal, and environmental element was positioned visually first, then its Photoshop coordinates were transferred into the matching data record. Keeping the design image and game coordinate space aligned made it possible to translate the composed level directly into the SFML world while retaining control over spacing, traversal, and visual layering.

Moving platforms retain their original position and apply a sinusoidal vertical displacement using elapsed game time and their configured amplitude. Every level element is then passed to the player's collision integration. Platforms use previous and current player bounds to resolve landings, ceiling impacts, and side contacts without allowing fast movement to skip completely through a surface. Trap intersections apply upward and horizontal knockback, while a goal intersection during a jump marks the level as complete.

The gameplay camera initially uses a view matching the application window. Once the player moves beyond half the visible width, its horizontal centre follows the player. Camera-relative environmental layers are repositioned against the current view, and foreground elements move using a larger factor than the camera displacement to create parallax depth. When the player falls below the world boundary, both the player position and camera are reset.

Level completion is coordinated by the level screen and the supplied screen-management framework. Completing level one clears its objects and resource collections, selects level two, and loads the second set of data and artwork. Completing level two exits the gameplay screen so the menu beneath it becomes active again. Rendering uses the manager's current active-screen collection, ensuring a completed and cleaned-up level is not rendered for an additional frame.

## Contributors

- Ash - group project contributor
- Jack Gore - Level Developer
- Sam - group project contributor
- Josh - group project contributor
- Dr Chris Carter - author of the university-supplied LJMU framework/template

## Disclaimer

This project was developed collaboratively as commissioned coursework for university assessment. The source code presented here is published solely for educational and portfolio purposes only. No permission is granted to reproduce, distribute, submit, or adapt it without prior written permission.
