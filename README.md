# SimpleSDLWrapper

SimpleSDLWrapper is a set of classes designed to automate some of the more tedious and hard-to-learn parts of SDL. Because of this, **almost all non-essential features are missing**. For example, the only shape a clickable screen area can currently take is a rectangle. The guiding design principle of this library is to make simple SDL projects easy to start.

## Basic Data Structures

See the [wiki page](https://github.com/jett0286/SimpleSDLWrapper/wiki) for more in-depth descriptions

### SSW_Window
This is the main data structure the user interfaces with. It is used to interface with the graphics manager and the input manager. Currently, this is all it does.

### SSW_GraphicsManager
This is the data structure controlling everything drawn to the screen. It contains a list of GraphicsElements, each of which are rendered to the screen whenever a refresh function is called. 

### SSW_GraphicsElement

These are the classes that determine what happens when the screen refreshes. Each contains a virtual render() function, executed on each refresh.

- **SSW_GraphicsElement_Base**: This is a purely virtual class that is the parent of all other graphics elements.
- **SSW_GraphicsElement_SolidColor**: This simply draws a solid-colored rectangle to the screen
- **SSW_GraphicsElement_Sprite**: This uses the Sprite data structure to draw a bitmap image to the screen.
