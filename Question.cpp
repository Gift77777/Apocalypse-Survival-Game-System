#include "Question.h"
#include <vector>

using namespace std;
    /*struct StoryText {
        string storyText;
        operator string() const { return storyText; }
    };

    struct QuestionData {
        string questionText;
        vector<string> options;
        int correctAnswerIndex;
        bool isTrueFalse;
        int difficultyLevel;
    };*/

    Question::Phase_1::Phase_1() {

            path1_Encounters = {
                {"The outbreak began suddenly. Hospitals are overwhelmed with patients showing violent symptoms. You're at home watching the news as cities go into lockdown."},
                {"Your neighbor knocks on your door, coughing violently. He says his wife has been bitten by something and needs help."},
                {"The power goes out. On the radio, you hear reports of attacks spreading through the downtown area."},
                {"A news alert shows footage of people attacking others in the streets. The anchors say to stay indoors."},
                {"You hear glass breaking next door. Through the window, you see your neighbor attacking his own family."},
                {"Your phone buzzes with an emergency alert: 'Shelter in place. Avoid contact with anyone showing aggression or disorientation.'"},
                {"The TV comes back on with a distorted government message about 'containment procedures' before cutting to static."},
                {"You hear scratching at your back door. Something is trying to get in."}
            };

            // Phase 1 - Basic survival questions (in chronological order)
            path_1 = {
                // Question 1
                {"You hear screams outside. The TV shows riots downtown. What's your first move?",
                {"Barricade the doors and windows", "Go outside to help",
                 "Call 911", "Grab a weapon"},
                0, false, 1},

                // Question 2
                {"Your coughing neighbor asks to come inside. What do you do?",
                {"Let him in and try to help", "Tell him to go to the hospital",
                 "Give him supplies through the window", "Ignore him completely"},
                2, false, 1},

                // Question 3
                {"True or False: The infected can be reasoned with or calmed down.",
                {"True", "False"},
                1, true, 1},

                // Question 4
                {"The power is out. What should you prioritize securing first?",
                {"Flashlights and batteries", "Perishable food",
                 "Entertainment", "Valuables"},
                0, false, 1},

                // Question 5
                {"True or False: Headshots are the only way to stop the infected permanently.",
                {"True", "False"},
                0, true, 1},

                // Question 6
                {"You see infected people outside. How should you move if you must go out?",
                {"Run as fast as possible", "Move quietly and stay low",
                 "Make noise to scare them away", "Wait until daylight"},
                1, false, 1},

                // Question 7
                {"True or False: Fire is an effective weapon against the infected.",
                {"True", "False"},
                0, true, 1},

                // Question 8
                {"Where should you fortify as your safe room?",
                {"Basement", "Attic",
                 "Master bedroom", "Bathroom"},
                0, false, 1}
            };
    }
    

    

   Question::Phase_2::Phase_2() {
            path1_Encounters = {
                {"After a week in lockdown, supplies are running low. You spot a National Guard truck abandoned down the street."},
                {"At night, you see figures moving differently - faster, more coordinated. They're watching the houses."},
                {"The radio mentions a new strain spreading - infected that can run and climb."},
                {"You find a wounded soldier who says his unit was overrun by 'something smarter'."},
                {"The soldier warns that the new infected seem to be learning from their mistakes."},
                {"Your water stops running. You'll need to venture out soon or dehydrate."},
                {"The soldier dies overnight. You notice his fingers twitching unnaturally."},
                {"You hear something testing your barricades, methodically checking weak points."}
            };

            // Path 1 - Medium difficulty (chronological order)
            path_1 = {
                // Question 1
                {"The abandoned military truck might contain:",
                {"Weapons and ammo", "Medical supplies",
                 "Food and water", "All of the above"},
                3, false, 2},

                // Question 2
                {"True or False: The new infected can open doors and windows.",
                {"True", "False"},
                0, true, 2},

                // Question 3
                {"The wounded soldier needs medical attention. You should:",
                {"Use your limited supplies on him", "Put him outside",
                 "Keep him restrained in case he turns", "Euthanize him now"},
                2, false, 2},

                // Question 4
                {"To safely check the military truck, you should:",
                {"Go at dawn when infected are less active", "Sneak out at night",
                 "Wait for a rainstorm to mask your noise", "Create a distraction first"},
                3, false, 2},

                // Question 5
                {"True or False: The new infected avoid bright light.",
                {"True", "False"},
                1, true, 2},

                // Question 6
                {"Your water supply is gone. The safest source is:",
                {"The neighbor's pool", "Water heater tank",
                 "Toilet tanks", "All of the above"},
                1, false, 2},

                // Question 7
                {"True or False: The soldier's body should be burned immediately.",
                {"True", "False"},
                0, true, 2},

                // Question 8
                {"The infected are learning. You should:",
                {"Change your defense patterns", "Stay perfectly quiet",
                 "Set traps", "All of the above"},
                3, false, 2}
            };

            path2_Encounters = {
                {"You failed to secure supplies. The infected have surrounded your neighborhood."},
                {"At night, you hear them communicating with clicks and growls."},
                {"Your last radio battery dies with a warning about 'hive behavior' spreading."},
                {"You spot infected setting up what looks like ambush positions."},
                {"The electricity comes back on briefly - long enough to see dozens of shapes outside."},
                {"Something heavy hits your roof. Then another. They're coming from above now."},
                {"Your last neighbor's screams are cut off abruptly. You're alone now."},
                {"The barricades won't hold much longer. You need an escape plan."}
            };

            // Path 2 - Harder difficulty (chronological order)
            path_2 = {
                // Question 1
                {"True or False: The infected are actively hunting rather than just attacking.",
                {"True", "False"},
                0, true, 3},

                // Question 2
                {"The clicking sounds likely mean:",
                {"They're communicating", "They've found prey",
                 "They're in pain", "All of the above"},
                0, false, 3},

                // Question 3
                {"To escape your surrounded house, you should:",
                {"Fight through the front", "Go out the basement window",
                 "Wait for them to leave", "Use the attic vents"},
                1, false, 3},

                // Question 4
                {"True or False: The infected will give up if they can't find you.",
                {"True", "False"},
                1, true, 3},

                // Question 5
                {"Your best chance at survival is reaching:",
                {"The hospital downtown", "The police station",
                 "The highway out of town", "The sewer tunnels"},
                3, false, 3},

                // Question 6
                {"In the sewers, you'll need to watch for:",
                {"Other survivors", "Infected lying in wait",
                 "Flooding", "All of the above"},
                3, false, 3},

                // Question 7
                {"True or False: The water will protect you from infection.",
                {"True", "False"},
                1, true, 3},

                // Question 8
                {"The exit is blocked. You should:",
                {"Find another route", "Wait for help",
                 "Fight through", "Give up"},
                0, false, 3}
            };
   }
    

    Question::Phase_3::Phase_3() {
            // Best ending path (completed all phases well)
            path1_Encounters = {
                {"You've reached a military safe zone. The soldiers say you're the first survivor to make it this far."},
                {"The commander asks for your help - they've developed an experimental cure but need a live specimen."},
                {"Scouts report a hive of infected in the old hospital. The commander believes their leader holds the key."},
                {"You volunteer to lead the mission. The team prepares specialized sonic weapons based on your experience."},
                {"Inside the hospital, you find hundreds of dormant infected standing motionless."},
                {"At the center, a massive mutated infected seems to be controlling the others telepathically."},
                {"The sonic weapons disrupt the hive mind. You capture the alpha and retreat as the others collapse."},
                {"Back at base, scientists synthesize a cure from the alpha's blood. You're given the first dose."}
            };

            path_1 = {
                // Question 1
                {"True or False: The dormant infected will wake if disturbed.",
                {"True", "False"},
                0, true, 3},

                // Question 2
                {"What's the safest way to capture the alpha?",
                {"Use brute force", "Lure it with sound",
                 "Cut it off from the hive", "All of the above"},
                2, false, 3},

                // Question 3
                {"The sonic weapons should target:",
                {"The alpha's head", "The hive connection points",
                 "The building supports", "Random frequencies"},
                1, false, 3},

                // Question 4
                {"True or False: The alpha can control other infected telepathically.",
                {"True", "False"},
                0, true, 3},

                // Question 5
                {"If separated from the hive, the infected:",
                {"Become feral", "Shut down",
                 "Turn on each other", "All of the above"},
                1, false, 3},

                // Question 6
                {"True or False: The cure can reverse late-stage infection.",
                {"True", "False"},
                1, true, 3},

                // Question 7
                {"Final choice: how should the cure be distributed?",
                {"Military first", "Medical staff",
                 "Civilians", "Your group"},
                1, false, 3},

                // Question 8
                {"The scientists want to study you because:",
                {"You resisted infection", "You defeated the alpha",
                 "You show immunity", "All of the above"},
                3, false, 3}
            };

            // Good ending path
            path2_Encounters = {
                {"You've reached a survivor camp outside the city. The guards are suspicious of newcomers."},
                {"They put you through decontamination and interrogation before letting you in."},
                {"The camp leader explains some people carry the infection without symptoms."},
                {"You're assigned to guard duty. The rules are strict: no contact with outsiders."},
                {"On patrol, you find a group of uninfected children hiding in a store."},
                {"The commander orders them left behind - 'too risky'."},
                {"Your squad debates disobeying orders. The penalty is banishment."},
                {"The oldest child whispers that her little brother might be immune."}
            };

            path_2 = {
                // Question 1
                {"True or False: The camp is completely secure.",
                {"True", "False"},
                1, true, 3},

                // Question 2
                {"The decontamination process involves:",
                {"Blood tests", "Quarantine",
                 "Behavioral exams", "All of the above"},
                3, false, 3},

                // Question 3
                {"True or False: Asymptomatic carriers can turn suddenly.",
                {"True", "False"},
                0, true, 3},

                // Question 4
                {"The children show no symptoms. You should:",
                {"Follow orders", "Sneak them in",
                 "Give them supplies", "Test them first"},
                3, false, 3},

                // Question 5
                {"The real reason for no-contact orders is:",
                {"Prevent infection", "Conserve resources",
                 "Maintain control", "All of the above"},
                2, false, 3},

                // Question 6
                {"True or False: The immune child could save humanity.",
                {"True", "False"},
                0, true, 3},

                // Question 7
                {"Final choice: what will you do about the children?",
                {"Leave them", "Sneak them in",
                 "Stay with them", "Tell the commander"},
                1, false, 3},

                // Question 8
                {"If caught disobeying orders, you'll be:",
                {"Executed", "Banished",
                 "Imprisoned", "Infected"},
                1, false, 3}
            };

            // Bad ending path
            path3_Encounters = {
                {"You're trapped in an office building as infected swarm the streets below."},
                {"The military bombs shake the city. The power flickers on and off."},
                {"A doctor hiding with you says the infection has mutated - it's airborne now."},
                {"The rooftop helipad is your only hope, but the stairwell is blocked."},
                {"You find makeshift weapons in the office kitchen. The infected are learning."},
                {"The doctor reveals she's been bitten but is resisting the infection somehow."},
                {"The top floor is barricaded by panicked survivors who won't let anyone in."},
                {"The building groans as another bomb hits. Time is running out."}
            };

            path_3 = {
                // Question 1
                {"True or False: The airborne strain is less deadly.",
                {"True", "False"},
                1, true, 3},

                // Question 2
                {"How to reach the roof without stairs?",
                {"Elevator shaft", "Window scaffolding",
                 "Air vents", "All of the above"},
                0, false, 3},

                // Question 3
                {"True or False: Office supplies make effective weapons.",
                {"True", "False"},
                0, true, 3},

                // Question 4
                {"The doctor resisting infection suggests:",
                {"Natural immunity", "Partial cure",
                 "Delayed reaction", "All of the above"},
                3, false, 3},

                // Question 5
                {"How to get past the barricaded survivors?",
                {"Negotiate", "Force",
                 "Find another way", "Wait them out"},
                2, false, 3},

                // Question 6
                {"True or False: The bombs will destroy all infected in the area.",
                {"True", "False"},
                1, true, 3},

                // Question 7
                {"Final choice: what to do about the doctor?",
                {"Take blood samples", "Leave her behind",
                 "Try to cure her", "Euthanize her"},
                0, false, 3},

                // Question 8
                {"When the building collapses, you should:",
                {"Head for basement", "Jump to adjacent building",
                 "Shelter in place", "Run through infected"},
                1, false, 3}
            };

            // Worst ending path
            path4_Encounters = {
                {"You're alone in the ruins, wounded and exhausted. The infection burns in your veins."},
                {"Hallucinations mix with reality. The infected seem to whisper your name."},
                {"You find a pistol with one bullet. The ultimate choice looms."},
                {"Memories flash - loved ones lost, mistakes made. The pain is constant."},
                {"A rainstorm begins, washing blood into the gutters. The infected hate water."},
                {"Your vision blurs between human and infected sight. Which is real?"},
                {"The final night falls. They're coming. You can feel their hunger."},
                {"The pistol feels heavy in your hand. One shot left..."}
            };

            path_4 = {
                // Question 1
                {"True or False: The whispers are real.",
                {"True", "False"},
                0, true, 3},

                // Question 2
                {"The rain provides an opportunity to:",
                {"Escape", "Find clean water",
                 "Hide your scent", "All of the above"},
                3, false, 3},

                // Question 3
                {"True or False: Your wound will kill you before the infection does.",
                {"True", "False"},
                1, true, 3},

                // Question 4
                {"The pistol should be used to:",
                {"Fight", "Signal",
                 "Self-deliverance", "Save last bullet"},
                2, false, 3},

                // Question 5
                {"Final thought before the end:",
                {"I tried", "I regret",
                 "Why me?", "No one left"},
                0, false, 3},

                // Question 6
                {"True or False: Someone will remember your name.",
                {"True", "False"},
                1, true, 3},

                // Question 7
                {"Your final act should be:",
                {"Go down fighting", "Find peaceful place",
                 "Record message", "Let the rain wash you away"},
                3, false, 3},

                // Question 8
                {"The infection's final gift is:",
                {"Peace", "Strength",
                 "Understanding", "Nothing"},
                3, false, 3}
            };
    }
    
