# Software Requirements and Specification
## Motivation
The motivation of this document refers to document `document-name` part `document part`.
## Objective
The objective of this document is to provide technical requirements for software development which is measurable and can be used as reference to produce deterministic software mechanism. 
### Rule and Convention
This section will discuss about the rule and convention of the requirement to provide consistency and standard.

The requirement shall state the expected functionalities which is specific for a set of specific input and produced output with a set of specifications. The format of the requirement shall be in form of the following (this is the requirements requirements):
1. Requirement shall has semantic naming or standard code accross organization.
2. Requirement shall be grouped in a consistent context, to guide modularity.
3. Requirement shall has paragraph of wording which may help developer to understand the background of the functionality.
4. After the wording, requirement shall display one or more diagrams which can be flow-chart, use case diagram, input-process-output diagram, cause/effect matrices or other diagram.
5. Requirement shall also have a level of specification which has explanation along with the diagram(s) with the format:
   1. Input atomic parameter explanation, what shall be covered (in-scope) and what shall not be covered (out-scope).
   2. process explanation, what shall be covered (in-scope) and what shall not be covered (out-scope).
   3. Output atomic parameter explanation, what shall be covered (in-scope) and what shall not be covered (out-scope).
   4. Side effect explanation, what will be affected and what not to be affected.
   5. How this functionality is accessed (by user or by othe system/sub-system), including options of the access, for example: function add user can be accessed via command line interface or via web-based interface.
   6. Provide real world example of the functionality. 

### Expected Action
The expected action from this section is a derivative work from document complete section of general functional requirement of the software. This derivative work can be put in this document as a following section (thus, this document would be a live document which will be finalized after all expected derivative work is approved), or to be put on a linked separate document.
## Derivative Works
This section is a response for the previous section (since all party of this initiative are in internals in the organization). This section shall be containing at least two part: a *general functional requirement* which reflects features that user wants and a *unit function specification* which is break-down of the *general functional requirement* to be unit sub-functions which is unit testable (and for TDD initiation).
### General Functional Requirements
the development is to build a set of software which helping video streaming chanel maintenance to:

|No|Group|Functional Name|
|---|---|---|
|1|Core|Generate video from configuration file|
|2|Core|Generate vector image from configuration file|
|3|Access|Accept cascading command line instruction|
|4|Access|Accept command via secure and authenticated REST API|
|5|Management|User management|
|6|Management|Video management|
|7|Management|Reusable resource management|
|8|Workspace|Upload reusable unit and/or its configuration|
|9|Workspace|Create/edit/view reusable unit and/or its configuration|
|10|Workspace|Create/edit/view reusable object configuration|
|11|Operation|Create/edit/view video scene objects plan|
|12|Operation|Create/edit/view video scene scenario plan|
|13|Operation|Generate video from scene scenario & objects plan|
|14|Operation|Publish video to video streaming platform|
|15|Operation|Create/edit/view schedule for video auto publishing|
|16|Operation|Video streaming platform dashboard connectivity|
|17|Operation|Video streaming platform analytics connectivity|
### Unit Function Specifications
#### 1. Generate video from configuration file
1. Read configuration file
   1. Read objects from file
   2. Read scenario and timeline
   3. Read textual reference for generating speech
2. Draw Object in scenario timeline in multi image files
3. Generate voicing from text-to-speech
4. Combine all image as a single video file along with the generated sounds
#### 2. Generate vector image from configuration file
1. Read snapshot frame index from configuration file (*unit-testable*)
2. Read snapshot specification from configuration file (*unit-testable*)
3. Draw vector file for the frame index following the specification (*mock-testable*)
#### 3. Accept cascading contextual command line instruction
1. Define root command (*mock-tastable*)
2. Define children commands (*multiple*; each *mock-testable*)
#### 4. Accept command via secure and authenticated REST API
#### 5. User management
#### 6. Video management
#### 7. Reusable resource management
#### 8. Upload reusable unit and/or its configuration
#### 9. Create/edit/view reusable unit and/or its configuration
#### 10. Create/edit/view reusable object configuration
#### 11. Create/edit/view video scene objects plan
#### 12. Create/edit/view video scene scenario plan
#### 13. Generate video from scene scenario & objects plan
#### 14. Publish video to video streaming platform
#### 15. Create/edit/view schedule for video auto publishing
#### 16. Video streaming platform dashboard connectivity
#### 17. Video streaming platform analytics connectivity
