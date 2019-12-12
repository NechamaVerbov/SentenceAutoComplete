## google-project-NechamaVerbov 11-12.12.2019 (As part of Excellenteam bootcamp)

# Sentence auto complete

### The project returns the best completion options for a given prefix of sentence:

The user starts typing the sentence he's in search for, the program recievs the partial sentence that was typed and returns 5 of the best options for completion.
In order for the completion options to apear quickly we work in two phases: offline and online.

Offline- We run offline a program that will parse all the possible sentences into a map with keys representing the prefix.
         After parsing to a map it will only take the program when its online O(1).
         
Online- We recieve the prefix and access the map we have from the Offline phase with prefix being the key.
        As we said the time complexity is O(1). 
        If there's a hit: The values returned from the map are the completion options for the prefix.
        If there's a miss: We calculate the best completion by assuming he was one charater wrong.


### Implementation:

The project was implement with C++17 in Linux.
The design is based on MVC architectural pattern that separates an application into three main logical components: the model, the view, and the controller. Each of these components are built to handle specific development aspects of an application.


### Special thanks:

* Excellenteam bootcamp mentors

Google personnel:
* Hassan
* Avi


