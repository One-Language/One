# SUMMARY

## Why do you need to use programming languages?

In our world, almost everything is being done with or by computers, everyone knows that. But, what everyone doesn't know is that everyone can use programming languages. You don't have to be a cool Holywood hacker or an 250 IQ IT guy. Computers (softwares) can help you whoever you are. If you are a designer, you would love to have a software that tells you what keywords you can use, wouldn't you? Or let's assume that you are a translator. You are living with the fear of being unemployed due to computers and translation AIs. Why are you waiting for them to steal your job? Use them to improve your job.

## Why should you learn them?

I believe we have agreed that we will not let the computers have our jobs but we will use them for us. So, how are we going to do that? Are we going to spend hundreds of dollars for every software and script we need? Are we going to hire a programmer for ourselves? No, you should learn how to write and use programs yourself.

Don't be afraid, it is not hard. It's actually piece of cake. Also, you have an aim to reach. This will make things even easier for you. Who knows, you can be a programmer yourself one day. Just start now, and the rest will come.

## Where to start?

Alright. You learned what programming languages are and why should you learn them. But there are about 700 programming languages out there and no one would learn all of them to use them not to lose their jobs or to get support from them.

So, what these people who can use programming languages do? They learn to use the one that they will use most and the one from which they will benefit. If you want to deal with statics and data, you should learn Python or if you want to create executable programs, you should learn C, etc.

**BUT WE HAVE A GAME CHANGER HERE: THE ONE.**

For all of your purposes, whether it is creating a website or writing an executable program, you should learn **One**.

## What is One?

One is an open source, self-hosted, bootstapping programming language. It is being developed by [Max](github.com/BaseMax), [John](github.comjbampton) and our contibutors.

It's name is One because the aim of the language is providing users a single programming language to learn and use for every kind of problem they need to solve.

## Getting started with One

One sounded to you as a dream and you are interested in it but you don't know where to start. You start here by reading this **Getting started with One** guide.

<!--
We should add a section here about installing One
-->

### What programming languages do?

Imagine there are three people: a French, an English and a translator. The French guy doesn't speak English and the English guy doesn't speak French. The English guy has to do something but he doesn't know what is his mission. His mission should be told him by the French guy but he can't speak English. So, they need a translator to understand each other.

A programming language is like an translator who translates everything you say into the computer's language. So that, computer can understand you and follow your orders. As it is a language, it has it's own grammar rules and we call it "the syntax".

<!--
### The Syntax of One
the syntax part should be added here
-->

### What is input and output?

Computers can hear and speak too. That's how they are communicating with us. Of course, we don't speak about your microphone and webcam. Then how are they communicating with us? With inputs and outputs.

Input is everything you do to make computers do something. For example, pressing a key on keyboard is an input or clicking with your mouse is an input.

Output is the reaction that your computer give. When you click on a file on your desktop you give the computer an input and in return, computer gives you an output by opening that file.

This process is important to understand and understanding this process will make things lighter for you.

### What are variables?

Variables are containers for storing values.

Do you remember the translator analogy? Every time a word is told in French, the translator keeps the word in his mind and returns it when necessary.

In programming languages, we can create variables to store data and to use it when necessary.

``` text
hello = bonjour
car = voiture
love = amour
```

In the example above, `hello` is the name of the variable and `bonjour` is the value returned in it. We keep that information in mind because we believe we will need it in the future.

<!--
Assigning value to a variable section should be added here.
Variable types section should be added here.
-->

### What are if/else conditions?

While we are talking with our computers, we may need to tell them some conditional cases. In such situations, we use if/else statements and give computers more than one case and more than one option.

``` python
if hello = bonjour:
    print("'Bonjour' means 'Hello' in French")
```

In the code above, the computer will print `"Bonjour" means "Hello" in French` as `hello = bonjour` but what if the condition wasn't fulfilled? Then, the computer wouldn't do anything because we didn't tell it to do. Let's give computer an else condition.

``` python
if hello = merhaba:
    print("'Merhaba' means 'Hello' in Turkish)
else:
    print("I don't know the language you are speaking")
```

So, we gave the computer an if condition, which will be executed if the condition is met, and an else condition, which will be executed if the condition is NOT met. If we run the program above and give computer a word other than in French and Turkish, the computer will say us:
`"I don't know the language you are speaking"`

If/else statements are basically that. You will learn more about them in future but do not forget, this is a getting started guide.

### What are the functions?

Let's assume you are writing a program but you need to use a part of your program multiple times. It would be boring and tiring to write the same lines over and over again, right? If you agree with me, you may want to learn how to use functions.

Functions are basically a little piece of code that you use over and over again in your program. Instead of writing the same lines every time you need a feature that you've created, you can define a function and simply use it again and again. It's easier and quicker.

Let's remember our translator analogy.

```python
if hello = merhaba:
    print("'Merhaba' means 'Hello' in Turkish")
else:
    print("I don't know the language you are speaking")
```

Instead of writing these lines with only changing them a little, you can define a function.

```python
def translator(word):
    if hello = word:
        print(word + "means 'Hello'.)
    else:
        print("I don't know the word you said")
```

Now, we have defined a function which takes `word` as input and checks if this word means `Hello`. If it does, it prints

```text
word means 'Hello'.
```

if it doesn't, it prints:

```text
I don't know the word you said.
```
