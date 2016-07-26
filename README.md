# Squares

2D squares game

## TODO

- I don't like how events are handled (SystemEvent.hpp).
- Sounds are badly managed. Right now every window could have their sounds. But what happens when we want to update all sounds level? Currently we do this with SystemEvent to tell all windows to update their sounds, but I don't really like that.
