# JUST THE UPGRADES
Designed to compare two Magic: The Gathering decks: the deck you currently have and the deck you want. It provides a list of the cards you already have and identifies which cards you need to acquire to complete your desired deck.

I made this application for myself because I am in the process of upgrading one of my magic the gathering commander decks. I found an upgraded decklist online but I already had some of the cards and I wanted to know which cards I needed to acquire. So instead of writing down each one and knowing which card it would replace in my deck, I made a program to do that for me. 

Everything is hardcoded because again, this applciation was just for my sake but I do plan on making a website application that will accomplish more of what I have in mind for the future development of this program. 
## Lessons Learned

This was my first time delving into c++ so I learned a lot about the syntax and quirks of the language. For example, I learned what a size_t data type was, how adding an ampersand changes arguments in your function, etc. 
ALSO, learned about thinking ahead on what data structures to use, because at first I was going to use a list for everything but I realized how slow that process is, even if this is a small application I wanted to do best practices and whatnot. So I ended up changing my code to use unordered_maps instead because it made more sense for the goal I was trying to accomplish with my program. 
## Roadmap
- Implement a way to show costs of the upgrades, but to do that I need to use an API and I think just transitioning this project to a web application is the best strategy. 
- Show a visual of the upgrades, which again, would be handled by an api. 

Those are the main additions I have in mind that I would like to implement with the web application version of this program. 
