# Stickman Code Definition

Stickman is a basic programming language, just code and see the person move!

### Code entry point
The code's entry point is defined as:
```
start {
	some code
}
```

### Variables types
There are 4 varibles types:
1. `int`
2. `string`
3. `boolean`
4. `stickman`

### Variables declaration
Type | Declaration | Declaration and initialization
--- | --- | ---
`int` | `int varName;` | `int varName = 1`
`string` | `string varName;` | `string varName = "text"`
`boolean` | `boolean varName;` | `boolean varName = true`

### Comments
There are multiline comments, they must be surrounded by `/* Comment */`

### Usage of special variable stickman
The variable stickman represents the actual character that is showing on the screen. It can be controlled by executing different actions on the instance of the variable which are explained below. It also includes some attributes to know about the character status.

##### Atributes
The variable type stickman has certain modifiable attributes which gives you information about the character status:
1. `direction` : shows in which direction the character is facing and can have values of `left` , `right` and `front`.
2. `position` : shows in which position of the screen the character is standing. Can adopt integer values from 1 to 12 or use the constants `eosL` (end of screen left) and `eosR` (end of screen right).

This attributes can be accessed by typing an instance of stickman followed by an attribute with a "." as a delimiter for example:
```
...
stickman man;
man.direction = left;
if (man.position == eosL){
	man.direction = right;
}
...
```
##### Actions
The character can be controlled by excuting actions on it for making it move along the screen. The actions available on the included library are:
1. `walk` : the character moves in the direction specified by the attribute `direction`
2. `jump` : the charachter jumps.
3. `squat` : the character squats.
4. `yield "some text"` : the character yields the string followed by this action.
5. `moveLeftArm` : the character raises it´s left arm if it´s down and lowers it down if it´s up
6. `moveRightArm` : the character raises it´s right arm if it´s down and lowers it down if it´s up

The actions are exectued with an instance of stickman followed by an "->" and an action.
```
...

stickman man;
while(true){
	if(man.position == eosL){
		man.direction=right;
		man->jump;
	}
	if(man.position == eosR){
		man.direction = left;
		man->jump;
	}
	man->move;
}

...

```
##### Joining two actions
Two actions can be exectued at the same time using the  "+" operator. For example:
```
/* The following code makes the character
 * jump and move every two moves */

while (true){
	if (man.position%2 == 0){
		man->jump + man->walk;
	}
}
```


For adding additional movements check section "Adding additional movements"

### Functions definitions
Functions can be defined in any part of the document. To declare a new function you should write a code as:

```
func myFunc( parameters_list ) -> ReturnType {
	/* Some code */
}
```

All functions must start with the reserved token `func`, followed by a unique name that identifies it. Surrounded by parenthesis it's a `parameters_list` where you can send values to use inside de function. And finally the return type is specified, if the function don't returns, the `-> ReturnType` should be omitted.

Some example functions can be:

```
func jumpAndWalk( stickman man ) {
	man->jump + man->walk;
}
```

```
func add( int a, int b ) -> int {
	return a + b;
}
```



### Adding additional movements
There is a basic set of movements included in every stickman code. If you need more you are free to create them and include them.
To include an external library of movements you need to add a the following code before the `start` function.
```
include yourFile.stLib

start {
	some code
}
```

Then you can use them as any other action.
