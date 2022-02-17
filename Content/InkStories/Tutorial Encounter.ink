INCLUDE InkVariables.ink

VAR timer = -1
VAR listen_enemy_hit = 0
VAR curr_enemy_hit = 0
->tutorialstart
=== tutorialstart ===
Oh you've finally Awoken. Took you long enough.

+ [What?]
    -> guardwhat
+ [Who are you?]
    -> guardwhoareyou
    
    
=== guardwhoareyou ===
Ah, your memory still must be hazy. Don't worry, everyone's forgetful when they first Awaken. You might not remember me but we are old buddies! I'm so glad we'll be together again, it'll be just like the old days!


+ [What do you mean awaken?]
    -> guardwhat
+ [Old days?]
    -> guardolddays


=== guardwhat ===
Oh right you don't know yet, silly me ha ha! Today is your first today, but I've experienced today hundreds, maybe thousands of times, understand?

+ [No]
    -> guardelaborate


=== guardolddays ===
We used to be town guards. This little village never had anything too crazy going on, so we spent most of our time sparring, drinking, or goofing off when we should have been keeping watch. Those days are gone now though; these days are much more exciting!

+ [What's so exciting about these days?]
    -> guardwhat
    
=== guardelaborate ===
Every day is the same day, get it? We're in an infinite loop ha ha!

+ [Is there a way to end the loop?]
    -> guardendloop
    
=== guardendloop ===
What? Why would we want the loop to end? In the loop we are infinite; in the loop we are eternal. You'll come to understand soon enough. For now, why don't we have a little friendly sparring match to jog your memory on how to fight.

+ [Okay]
    ->guardcombattutorial.start
+ [Sure]
    ->guardcombattutorial.start
+ [I can't really say no, can I?]
    ->guardnope
    
=== guardnope ===
Nope! <>
-> guardcombattutorial.start

=== guardcombattutorial ===

    = start
    ~ timer = -1
    Okay so first things first, you need to know how to attack. Walk up to me and press RB to try hitting me with your sword.
    + [Okay]
        {listen(1, -1, -1, -1, -1, -1, -1, "guardcombattutorial.hit")}
        ->END
    
    = hit
    ~ timer = 5
    Good! Next you need to know how to defend yourself. I'm going to attack you now. Don't panic, enemies will never attack you while text is being displayed, so feel free to read the dialogue and respond accordingly. However, you also need to keep your eye on the dialogue timer, represented by this ring that is closing in around the dialogue box. If the timer runs out, the dialogue box will disappear and the enemy will move in to attack. Now, press B to dodge my attack.
        + [Okay]
        {listen(-1, -1, -1, -1, -1, 1, -1, "guardcombattutorial.dodged")}
        ->END
    
    = dodged
    ~ timer = 4
    Nice! Dodging is a great evasive maneuver, as you can't be hit at the start of your dodge. But there is a much more effective, yet riskier way of repelling enemy attacks. Next time I attack you, try pressing LB to parry my attack. Make sure to time it just right!
        + [Okay]
        {listen(-1, -1, -1, 1, -1, -1, -1, "guardcombattutorial.parried")}
        ->END
    
    = parried
    ~ timer = 6
    Great! Looks like you more or less remember how to fight now. One last piece of advice: if you want your opponent to talk or respond to you, different people require different approaches. For some, whenever I gloat or taunt them, I have to rough 'em up a bit before they start spilling their guts, pun intended. Others respond better to a more passive approach. Use your best judgement in each encounter.
    + [Okay]
        ->guardcombat.start


=== guardcombat ===

    = start
    Now it's time for a real fight to the death! Come at me!
    
    + [What? I thought you said we were friends.]
    -> guardfriends
    
=== guardfriends ===
We are; this is your initiation into the loop. See, me and the other guards started this little game some years back.

+ [What game?]
    -> guardwhatgame
    
=== guardwhatgame ===
We all compete to see who can kill the most people in a single loop. Right now I think [GUARD CAPTAIN NAME] is in the lead.

+ [Why would you do that?]
->ending

=== guardwhydo ===
Because it's fun! Ha ha! Don't worry, if you die you'll wake up just fine back at your house.

->ending

=== magicclue ===
If you want to know more about the loop, there's a cave with suspicious runes in it on the north side of the island that you might want to check out. Those same runes can be found on the shrine just off the east of the island.

->ending
=== ending ===
-> END