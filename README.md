# Pong - ECS

A simple implementation of Pong using the ECS architectural pattern, C++17 and SFML.

## Components

- **CircularObject**: radius of round objects (e.g the ball);
- **Drawable**: tag component that indicates that the entity should be rendered;
- **Input**: tag component that indicates that the entity interacts with the keyboard;
- **Position**: center of mass of the entity;
- **RectangularObject**: width and height of rectangular objects (e.g the paddles);
- **Scoreboard**: scores of both players;
- **ScoreListener**: contains a function that is called whenever a player scores;
- **ScoringBounds**: the x coordinates of the scoring thresholds;
- **Velocity**: velocity of the entity;
- **Wall**: a line segment corresponding to a window wall and a corresponding normal vector.

## Entities

- Ball (CircularObject, Drawable, Position, ScoreListener, ScoringBounds, Velocity)
- Player Paddle (Drawable, Input, Position, RectangularObject)
- Bot Paddle (Drawable, Position, RectangularObject)
- Scoreboard (Drawable, Scoreboard, ScoreListener, Position)
- Wall (Wall)

## Systems

- Input: (Input, Velocity)
- Movement:
  - (Velocity, Position, CircularObject, Wall, RectangularObject)
  - (Velocity, Position, RectangularObject)
- Paddle Bounding: (Position, RectangularObject)
- Rendering:
  - (Drawable, Position, CircularObject)
  - (Drawable, Position, RectangularObject)
  - (Drawable, Position, Scoreboard)
- Scoring: (ScoringBounds, Position, ScoreListener)

