# Code Samples
---
This repository is intended to offer a sampling of code samples from a variety of applications, across multiple languages.

## Contents

  * #### Aerial Robotics:
  
Written in C++, this directory contains a dummy data provider and a linear regression calculator used by Texas Aerial Robotics. The samples available here are not what is currently in use, but instead represent the last iteration of the program that was purely my work. A demonstration of this code in action (in sequence with other modules developed by the team) is available on the [Texas Aerial Robotics Facebook Page](https://www.facebook.com/texasaerialrobotics/videos/371609939999780/)
  
  * #### CFD Samples:
  
 This directory contains a matlab scricpt which generated the definition file for the OpenFOAM fluid dynamics solver meshGen function. The mesh generated is based om parameters provided at the top file, and is curtailed for the specific problem at hand (flow around a circular cylinder with fixed boundaries). A visualization of one such mesh is provided, as rendered in Paraview.
 
  * #### Contagion Sim:
  
The Contagion simulation project represents the most fleshed out project in this repository. As its name implies, this porgram simulates the spread of an illness based on user provided parameters for spreadbility and innoculation rates, assuming both neighborly contact and random mixing of the population. This entry demonstrates object oriented fundamentals, as well as thorough program architecture and proper use of headers. While all files are documented in line (with the exception of the shell scripts used to automate input), a broad perspective of the project is available in the included excerpt from the final report submitted alongside the code. 

  * #### Fortran:
  
The selection included in the Fortran directory is a small program used to compare performance across various implementation and for matrix multiplication. A small readme is included, and in line commentary documents content.

  * #### JSC Export Safe:
  
One of the more interesting projects I have worked on, the application I developed at Johnson Space Center is unfortunately not cleared for sharing. However, an explanation of the process I used to develop the software bridge between thre Trick simulation framework and CFS is available in my cleared exit presentation. Additionally, a demonstration of its usage is available in the .mp4 video included, which shows CFS driving a rover between waypoints in Trick while communicating across my application. This project required working knowledge in C & C++, as well as proper usage of custom libraries and headers.

  * #### Wordcloud (input) Generator:
  
One of the oldest entries in this repository, this python script was used to generate a text file, which would then be loaded into a wordcloud generating website. Further seperating it from other projects included was the 'Hackathon" nature of its origin, as this script was requested with a deadline set in hours as opposed to days. The script remains "as is", with the exception of more thorough documentation added with its inclusion in this repository. The Wordcloud (input) Generator is included to demonstrate proper understanding of pythonic syntax, program structring under time constraitns, and to serve as a basis for comparison with an OOP Python project that is currently under development.
  
