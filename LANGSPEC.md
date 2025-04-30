# Lox (language to implement) Specification.

## 3.2 High-Level Language.

### 3.2.-1 C like syntax.

Lox has c like syntax with some twist for simpler implementation

```c
print "asdf" // print doesn't have parentheses because it's actually a built-in statement and not a function
```

### 3.2.1 Dynamically Typed.

For the sake of simpler implementation Lox is created with dynamically typed capability.

### 3.2.2 Automatic Memory Management (Garbage Collection).

Lox implement its own Automatic Memory Management also called Garbage Collector.

## 3.3 Data Types.

### 3.3.1 Boolean.

```c
true; // Not false.
false; // Not *not* false.
```

### 3.3.2 Numbers.

Lox only has one kind of number, a Double Precision Floating Point.
```c
1234; // integers.
12.34; // floating number.
```

### 3.3.3 Strings

```c
"a string";
""; // also a string, but it's empty.
"123"; // guess what? this is string.
```

### 3.3.4 Nil (or Null in some language).
Lox use keyword `nil` to indicate if the value is `null` or doesn't exist.

## 3.4  Expressions.

### 3.4.1 Arithmetic.

```c
0 + 0; // addition - can be used both for numbers and strings.
0 - 0; // subtraction.
0 * 0; // multiplication.
0 / 0; // division.
```

Left and right side of Arithmetic expression is called **operands**, and the middle one is called **operator**.

There are two types of operator **fixed operator** (above examples), and **infix operator** (below example).
```c
-0;
```

### 3.4.2 Comparison and Equality.

```c
0 < 1; // less than.
1 > 1; // greater than.
i <= 1; // less equal than.
i >= 1; // greater equal than.
```

Equality expression can be used on two different types, but will always **never** equivalent.
```c
1 == 2; // false.
2 == 2; // true.

2 == "not a number"; // false.

2 == "2"; // will always false even though the number is equally the same.
```

### 3.4.3 Logical Operator.

#### 3.4.3.1 Not Operator (!).

```c
!false; // true.
!true; // false.
```

#### 3.4.3.2 "And" (and) and "Or" (or) Operator.

```c
false and true; // false.
false or true; // true.
```

### 3.4.4 Precedence and Grouping

Lox using known operator for Precedence and Grouping () - the parentheses.
```javascript
var average = (min + max) / 2; // expression inside parentheses evaluate first.
```

This book doesn't implement the rest of operators as bitwise, modulo, shift, and conditional operator.
> Try to implement it myself.


## 3.5 Statements

Basic statements.
```c
print "statement"; // evaluate single expression and display result to the end user.
"statement"; // using semicolon after expression promotes expression to the statement-hood.
             // the expression is evalueted but the result is often discarded.
```

Pack of statements can be achieved by using block statement.
```c
/* Block also affect scoping, which lead to next section. */
{
    print "One Statement";
    print "Two Statement";
}
```


## 3.6 Variables.

Variable can be declared with `var` statement, and can be reassign once created.
```javascript
var var1 = "123"; // declaring.
var1 = "456"; // reassign after declaration.
```

Unassigned variable value is `nil`.

## 3.7 Control Flow.

### If Statement.

```c
if (condition) {
    statement;
} else {
    else_statement;
}
```

### While Loop.

```javascript
var var1 = 0;

while (var1 == 0) {
    statement;
}
```

### For Loop.
```javascript
for (var i = 0; i < 12; i = i + 1) {
    statement;
}
```


## 3.8 Functions.

Lox function calling pretty much the same as common c like language.
Also, both parentheses are mandatory. Leaving them off doesn't call the function, it just refers to it.
```c
callingAFunctionWithArgs(arg1, arg2, andArg3);
callingAFunctionWithoutArgs();
```


Note:
- Arguments are value that is passed to the function, sometimes it's called **actual parameters**.
- Parameters are the variables that hold the value (arguments), sometimes it's called **formal parameters** or just a **formals**.

Defining function in Lox use `fun` keyword.
```
fun returnSum(a, b) {
    return a + b;
}
```

In Lox if the execution of function block doesn't return anything, it's explicitly returns `nil`.


### 3.8.1 Closures

Function are *first class* in Lox, which means it has real value that user can be referenced to.
```javascript
fun returnFunc(func) {
    return func;
}

fun lmao(b) {
    return "lmao" + b;
}

print returnFunc(lmao)(", hehe"); // lmao, hehe
```

A local function can also be declared inside the function.
```
func outerFunc() {
    func localFun() {}
}
```


## 3.9 Classes

### 3.9.4

Defining or declaring class in Lox just the same as another class based language.
```cpp
class Breakfast {
    cook() {
        print "masak lurd."
    }

    serve(who) {
        print "nih buat lo."
    }
}
```
The body of class (method) similar to how function were defined or declared.

```javascript
// storing class directly into variable.
var someVaribaleThatHoldsClass = Breakfast;

passingClassAsParameter(Breakfast);

```

Creating instance class is simple, just called it like it is a function.
```javascript
var classInstance = Breakfast(); // instantiating class.
print classInstance; // Breakfast instance.
```

### 3.9.5 Instantiation and Initialization.

Lox also allows user to freely add property to object.
```cpp
breakfast.meat = "meat";
breakfast.bread = "bread"; // if property doesn't exist it create new property.
```

Accessing class property within internal method also similar to the rest of class based language.
```javascript
class Breakfast {
    serve(who) {
        print "noh makan " + this.bread +
            " pakai " + this.meat + " bang, " + who;
    }

    //...
}
```

Initializer also can be declared inside class by adding `init()` method within the class definition.
```javascript
class Breakfast {
    init(meat, bread) {
        this.bread = bread;
        this.meat = meat;
    }

    //...
}

var baconAndToast = Breakfast("bacon", "toast");
baconAndToast.serve("LMAO"); // output: noh makan toast pakai bacon bang, LMAO
```

### 3.9.6 Inheritance

Lox use `<` keyword to indicate Inheritance in a class.
```
class Brunch < Breakfast {
    drink() {
        print "kembung bos.";
    }
}
```
From the example above, can be observed that `Brunch` is **derived class** or **subclass**, and `Breakfast` is the **base class** or **superclass**.

Every method defined in the superclass is also available in subclass.

Way to calling superclass's `init` method without polute subclass's `init` is by using `super` keyword.
```javascript
class Brunch < Breakfast {
    init(meat, bread, drink) {
        super.init(meat, bread);
        this.drink = drink;
    }
}
```

## 3.10 Standard Library.

`nil`.\n

Needs to be implemented.
