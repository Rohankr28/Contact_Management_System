# Contact_Management_System
A simple C++ console-based application that efficiently manages contacts using a Trie data structure. This project demonstrates how to add, search, delete, and display contacts based on prefixes, providing an effective way to organize and retrieve contact information.

Features
Add Contact: Add a contact name with its phone number.
Search Contact: Find contact details by name.
Delete Contact: Remove a contact from the list by name.
Display Contacts by Prefix: Show all contacts starting with a given prefix.
How It Works
The project uses a Trie data structure to enable fast insertions and lookups, particularly useful when dealing with large contact lists. Each contact name is stored as a path in the Trie, and phone numbers are associated with the final node of each contact name.

Getting Started
Prerequisites
Visual Studio Code (or any C++ IDE)
C++ compiler (e.g., g++)
