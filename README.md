## AstroSpiral

The Astro Spiral project presents an innovative way to compare astronomical images of the sky by building a convex spiral (using a modification of the Graham Scan algorithm for convex hull) according to the bright objects in a photo. On that purpose, an application for Windows and Mac OS X, written in C++, is developed using the Cinder toolbox.

### Introduction

How do astronomers find near-Earth asteroids (NEAs)? 

In the night sky, we can see stars shining with their own light - but how do we know they are actually stars? While all sky objects appear bright, some stars and galaxies radiate light, as opposed to the Moon, planets, natural satellites, comets, and near-Earth asteroids, which reflect light. How can we distinguish the two types of objects? 

Below, you can see a background of stars, which are too far from us to observe a difference in position. The asteroid BJ19377, on the other hand, is close enough, so we can see it moving in the sky.

![alt tag](http://iasc.hsutx.edu/images/astro.gif)

Astronomers have studied the sky in the search of asteroids for nearly 200 years, but they have not managed to find all the asteroids in our solar system yet. The search for asteroids is very important for the development of astronomy. Near-Earth asteroids are of great interest because of the resources of valuable materials which they posses. The danger of collision of the Earth with an asteroid passing close makes the search of asteroids useful to our society, too. Therefore, in recent years the study of asteroids is becoming extremely important as a warning of a possible dangerous collision, upcoming space landing missions and the research and development of asteroid resources.

![alt tag](http://www.rhysy.net/WIPS/Asteroids.jpg)

The task that is set is to create a software that builds a *convex spiral* according to the bright objects in an astronomical image of the sky. Given a set of astronomical images, taken successively by the same telescope, we can, very intuitively, by looking, to find differences in their spirals and thus finding star-like moving objects, which are most likely to be asteroids.

