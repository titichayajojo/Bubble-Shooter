
# Bubble Shooter

Bubble Shooter is a classic arcade puzzle game developed using Cocos2d-x, a cross-platform game development framework. The goal of the game is to clear the board by shooting bubbles and matching three or more of the same color to pop them.

## Features

- **Classic Puzzle Gameplay**: Match and pop bubbles to clear levels.
- **Cocos2d-x Framework**: Utilizes the powerful Cocos2d-x engine for cross-platform compatibility.
- **Multiple Levels**: Includes a variety of levels with increasing difficulty.
- **Customizable Settings**: Easily modify game parameters such as bubble speed, colors, and more.

## Installation

### Prerequisites

- Cocos2d-x (installed and configured)
- C++ compiler
- Android Studio (for Android builds) or Xcode (for iOS builds)

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/titichayajojo/Bubble-Shooter.git
   cd Bubble-Shooter
   ```

2. Set up Cocos2d-x:
   Ensure you have Cocos2d-x installed and configured on your system. Refer to the [Cocos2d-x setup guide](http://www.cocos2d-x.org/) for detailed instructions.

3. Compile and run the project:
   - For Android:
     ```bash
     cocos compile -p android --android-studio
     cocos run -p android --android-studio
     ```
   - For iOS:
     ```bash
     cocos compile -p ios
     cocos run -p ios
     ```
   - For desktop:
     ```bash
     cocos compile -p win32 # For Windows
     cocos compile -p mac   # For macOS
     ```

## Gameplay Instructions

- **Mouse or Touch Controls**: Aim and shoot bubbles to match colors.
- **Clear the Board**: Align three or more bubbles of the same color to remove them from the board.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

- Cocos2d-x for providing a versatile game development framework.
- Inspired by the original Bubble Shooter game.
