#combat variables
VAR LISTEN_enemyHits = 1
VAR COUNT_enemyHits = 0
VAR LISTEN_playerHits = -1
VAR COUNT_playerHits = 0
VAR LISTEN_enemyParries = -1
VAR COUNT_enemyParries = 0
VAR LISTEN_playerParries = -1
VAR COUNT_playerParries = 0
VAR LISTEN_enemyDodges = -1
VAR COUNT_enemyDodges = 0
VAR LISTEN_playerDodges = -1
VAR COUNT_playerDodges = 0
VAR LISTEN_timer = -1
VAR COUNT_timer = 0

VAR health = 50

VAR happiness = 50
VAR fear = 50
VAR anger = 50

#destinationKnots 
VAR enemyHitsKnot = "guardcombattutorial.hit"
VAR playerHitsKnot = ""
VAR enemyParriesKnot = ""
VAR playerParriesKnot = "guardcombattutorial.parried"
VAR enemyDodgesKnot = ""
VAR playerDodgesKnot = "guardcombattutorial.dodged"
VAR timerKnot = ""
VAR destinationKnot = ""

->guardfirstdialogue.tutorialstart

=== guardfirstdialogue ===

    = tutorialstart
    Oh you've finally Awoken. Took you long enough.

    + [Whats going on?]
        -> whoareyou
    + [Who are you?]
        -> whoareyou
    + [Who am I?]
        -> whoareyou
    
    
    = whoareyou
    Ah, your memory must be hazy. Don't worry, everyone's forgetful when they first Awaken. You might not remember me but we are old friends! I'm so glad we'll be together again, it'll be just like the old days!
    
    
    + [What do you mean by "Awaken"?]
        -> what
        
    + [Old days?]
        -> olddays


    = what
    Oh right you don't know yet, silly me ha ha! Today is your first today, but I've experienced today hundreds, maybe thousands of times, understand?
    
    + [No]
        -> elaborate
    + [Not really]
        -> elaborate
    + [We're in a loop?]
        -> yes


    = olddays
    We used to be town guards. This little village never had anything too crazy going on, so we spent most of our time sparring, drinking, or goofing off when we should have been keeping watch. Those days are gone now though; these days are much more exciting!
    
    + [What's so exciting about these days?]
        -> what
    + [What do you mean 'those days are gone'?]
        -> what
    
    = yes
    Yes! We're in an infinite loop ha ha!
    
    + [Is there a way to end the loop?]
        -> endloop
    + [What's causing the loop?]
        -> loopcause
    + [Sounds tedious.]
        -> tedious
    + [Sounds cool!]
        -> cool
    
    = elaborate
    Every day is the same day, get it? We're in an infinite loop ha ha!
    
    + [Is there a way to end the loop?]
        -> endloop
    + [What's causing the loop?]
        -> loopcause
    + [Sounds tedious]
        -> tedious
    + [Sounds cool!]
        -> cool
        
    = tedious
    What? The loop is the best thing to ever happen to us. In the loop we are infinite; we are eternal. In the loop we are free to do as we please. You'll come to understand soon enough.
    
    + [Well what exactly do we do with our infinite time?]
        -> soon
    = cool
    Right? In the loop we are infinite; we are eternal. In the loop we are free to do as we please. I am glad you understand.
    
    + [So how did the loop start?]
        -> loopcause
    + [So what do we do with our infinite time?]
        -> soon
        
    = soon
    Oh I'll get to that in a minute. For now, why don't we have a little friendly sparring match to jog your memory on how to fight, the island is dangerous right now.
    
    + [Okay]
        -> guardcombattutorial.start
    + [Sure]
        -> guardcombattutorial.start
    + [I can't really say no, can I?]
        -> nope
    
    = loopcause
    Hmmm... I don't know, I never really thought about it too hard. It never seemed that important, you know? Why question such a blessing? I guess [GUARD CAPTAIN NAME] might have mentioned something about the cave at the east end of the island once or twice. You could try checking that out, or maybe ask [GUARD CAPTAIN NAME] yourself, though she doesn't speak much, and when she does, it doesn't make much sense to me.
    
    + [Where can I find (GUARD CAPTAIN NAME)?]
        -> guardcaptaindirections
    
    + [Which end of the island is east?]
        -> directions
        
    = directions
    Oh right, you don't remember where anything is. This is the north side of the island, so east would be on the other side of the bay. The cave should be just past that cliff face. Also, [GUARD CAPTAIN NAME] should be in the town square right about now, up the hill just past the market, in case you were wondering.
    + [Okay]
        -> tutorialsegue
    + [Thanks for the directions]
        -> directionsthanks
    
    = guardcaptaindirections
    Oh right, you don't remember where anything is. She should be in the town square right about now, up the hill just past the market. And if you're wondering where the cave might be, this is the north side of the island, so east would be on the other side of the bay. The cave should be just past that cliff face.
    
    + [Okay]
        -> tutorialsegue
    + [Thanks for the directions]
        -> directionsthanks
        
    = directionsthanks
    No problem. <>
        -> tutorialsegue
    
    = tutorialsegue
    Now before you go off on your own, why don't we have a little friendly sparring match to jog your memory on how to fight, the island is dangerous right now.
    
    + [Okay]
        -> guardcombattutorial.start
    + [Sure]
        -> guardcombattutorial.start
    + [I can't really say no, can I?]
        -> nope
    
    = endloop
    What? Why would we want the loop to end? In the loop we are infinite; in the loop we are eternal. You'll come to understand soon enough.
    
    + [What's causing the loop?]
        -> loopcause
    
    = nope
    Nope! <>
    -> guardcombattutorial.start

=== guardcombattutorial ===

    = start
    # timer -1
    Okay so first things first, you need to know how to attack. Walk up to me and press RB to try hitting me with your sword.
    + [Okay]
        # {listenEnemyHits(1, "guardcombattutorial.hit")}
        ->END
    
    = hit
    # timer 15
    Good! Next you need to know how to defend yourself. I'm going to attack you now. Don't panic, enemies will never attack you while text is being displayed, so feel free to read the dialogue and respond accordingly. However, you also need to keep your eye on the dialogue timer, represented by this ring that is closing in around the dialogue box. If the timer runs out, the dialogue box will disappear and the enemy will move in to attack. Now, press B to dodge my attack.
        + [Okay]
        {listenPlayerDodges(1, "guardcombattutorial.dodged")}
        # function Start_Combat
        ->END
    
    = dodged
    # timer 10
    Nice! Dodging is a great evasive maneuver, as you can't be hit at the start of your dodge. But there is a much more effective, yet riskier way of repelling enemy attacks. Next time I attack you, try pressing LB to parry my attack. Make sure to time it just right!
        + [Okay]
        {listenPlayerParries(1, "guardcombattutorial.parried")}
        # function Start_Combat
        ->END
    
    = parried
    # timer 15
    Great! Looks like you more or less remember how to fight now. One last piece of advice: if you want your opponent to talk or respond to you, different people require different approaches. For some, whenever I gloat or taunt them, I have to rough 'em up a bit before they start spilling their guts, pun intended. Others respond better to a more passive approach. Use your best judgement in each encounter.
    + [Okay]
        ->guardcombat.start


=== guardcombat ===

    = start
    # timer 15
    Now it's time for a real fight to the death! Come at me!
    
    + [What? I thought you said we were friends.]
        {defaultListen("guardcombat.friends")}
        -> END
    + [Say your prayers.]
        {defaultListen("guardcombat.thatsthespirit")}
        -> END
    + [...]
        {defaultListen("guardcombat.nothingtosay")}
        -> END
        
    = thatsthespirit
    HA! That's the spirit! The other guards and I started this little game some years back. We all compete to see who can kill the most people in a single loop. Looks like you'll do well in this game of ours.
    
    + [Why start a game like that?]
        {defaultListen("guardcombat.whydo")}
        -> END
    + [Sounds exciting!]
        {defaultListen("guardcombat.exciting")}
        -> END
    + [That's horrible.]
        {defaultListen("guardcombat.horrible")}
        -> END
        
    = nothingtosay
    Nothing to say to me? Well while I have your attention you should know the other guards and I started a little game some years back. We all compete to see who can kill the most people in a single loop.
    
    + [Why start a game like that?]
        {defaultListen("guardcombat.whydo")}
        -> END
    + [Sounds exciting!]
        {defaultListen("guardcombat.exciting")}
        -> END
    + [That's horrible.]
        {defaultListen("guardcombat.horrible")}
        -> END
    + [...]
        {defaultListen("guardcombat.nowords")}
        -> END
        
    = nowords
    Ah yes, it is best to let our swords do the talking...
    
    + [Then why don't you ever shut up?]
        {defaultListen("guardcombat.shutup")}
        -> END
    + [...]
        {defaultListen("guardcombat.reminder")}
        -> END
        
    = shutup
    Ohhh I'm going to enjoy killing you. And you better get used to it, we have a lot of loops ahead of us.

    + [Enough talk, are we fighting to the death or not?]
        -> verywell
    
    = reminder
    You remind me of [GUARD CAPTAIN NAME]. She's not a big fan of talking, prefers actions to words.
    
    + [Enough talk, are we fighting to the death or not?]
        -> verywell
        
    = verywell
    Very well...
    
    +[...]
     ->END
    
    = friends
    # timer 15
    We are friends; this is your initiation into the loop. See, the other guards and I started this little game some years back. We all compete to see who can kill the most people in a single loop. Right now I think [GUARD CAPTAIN NAME] is in the lead.
    
    + [Why would you do that?]
        {defaultListen("guardcombat.whydo")}
        -> END
    + [Sounds exciting!]
        {defaultListen("guardcombat.exciting")}
        -> END
    + [That's horrible.]
        {defaultListen("guardcombat.horrible")}
        -> END

    = whydo
    # timer 15
    Because it feels good. We get to do whatever we want, whenever we want, to whoever we want. Isn't that amazing?
    
    + [Yeah!]
        {defaultListen("guardcombat.exciting")}
        -> END
    + [That's horrible.]
        {defaultListen("guardcombat.horrible")}
        -> END
    
    = exciting
    I'm happy you understand. Not everyone can see the beauty of the killing game. Now, no more talking, it's time for me to give you a proper welcome to the loop...
    + [Okay.]
        -> END
    + [Finally.]
        -> END
    + [...]
        -> END

    = horrible
    What? What do you mean horrible? It's not like we're really killing anyone, everything resets at the end of the day. The Unawoken don't even remember a thing.
    
    + [What about the Awoken?]
        {defaultListen("guardcombat.awoken")}
        -> END
    + [It makes no difference, you are causing suffering]
        {defaultListen("guardcombat.suffering")}
        -> END
        
    = awoken
    The Awoken may remember, but they will still be fine in the morning. Pain is temporary, glory is forever.
    
    + [You're disgusting]
        {defaultListen("guardcombat.disgusting")}
        -> END
    + [Fair enough]
        {defaultListen("guardcombat.fairenough")}
        -> END
    
    = suffering
    But that suffering ceases to exist at the end of the day, so each morning I am reborn with my morality intact.
    
    + [And what about the Awoken?]
        {defaultListen("guardcombat.awoken")}
        -> END
    + [They may not remember, but your actions are still your own.]
        {defaultListen("guardcombat.disgusting")}
        -> END
        
    = disgusting
    It looks like this conversation is going nowhere. Very well, you will come to appreciate my way sooner or later, we have all the time in the world. Now let me give you a proper welcome to the loop.
    
    + [...]
        # function Start_Combat
        -> END
        
    = fairenough
    I knew you would see it my way. Now then, let me give you a proper welcome to the loop.
    
    + [...]
        # function Start_Combat
        -> END
        

    = anger1
    Stop running away!
    
    + [Then stop trying to kill me.]
        ~ anger = anger + 5
        {defaultListen("guardcombat.storylets")}
        -> END
    + [No.]
        ~ anger = anger + 5
        {defaultListen("guardcombat.storylets")}
        -> END
    + [...]
        {defaultListen("guardcombat.storylets")}
        -> END
    
    = anger2
    I know I taught you how to dodge, but dodging is for losers. Stand your ground and fight back!
    
    + [Catch me if you can.]
        ~ anger = anger + 5
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Fine, prepare to die]
        ~ anger = anger - 10
        ~ happiness = happiness + 5
        {defaultListen("guardcombat.storylets")}
        -> END
    + [No.]
        ~ anger = anger + 5
        {defaultListen("guardcombat.storylets")}
        -> END
    + [...]
        ~ anger = anger + 5
        {defaultListen("guardcombat.storylets")}
        -> END
        
    = anger3
    <red>FIGHT BACK COWARD!</>
    
    + [We really don't need to kill each other]
    -> bored
    + [I can do this all day]
    -> bored
    
    + [Fine, prepare to die]
        ~ anger = anger - 10
        ~ happiness = happiness + 5
        {defaultListen("guardcombat.storylets")}
        -> END
    + [...]
    -> bored
    
    = bored
    Ugh fine, I was getting bored anyways.
    
    + [(leave)]
    -> END
    
    = happiness1
    Yes that's right, show me what you're made of!
    
    + [Prepare yourself!]
        ~ happiness = happiness + 5
        {defaultListen("guardcombat.storylets")}
        -> END    
    + [What is wrong with you?]
        {defaultListen("guardcombat.storylets")}
        -> END    
    + [...]
        {defaultListen("guardcombat.storylets")}
        -> END   
    
    = happiness2
    You must admit, you enjoy the thrill of battle too!
    
    + [I'm not as crazy as you]
        {defaultListen("guardcombat.storylets")}
        -> END   
    + [I fight out of necessity]
        {defaultListen("guardcombat.storylets")}
        -> END   
    + [yes!]
        ~ happiness = happiness + 5
        {defaultListen("guardcombat.storylets")}
        -> END   
    
    = happiness3
    HAHA THIS IS WHAT THE LOOP IS FOR
    
    + [You need therapy or something]
        {defaultListen("guardcombat.storylets")}
        -> END   
    + [AGREED]
        {defaultListen("guardcombat.storylets")}
        -> END   
    + [...]
        {defaultListen("guardcombat.storylets")}
        -> END   
    
    = deathsdoor
    <red>ha... *cough* well met Whale... now- *cough* finish the job</>
    
    + [(continue)]
        {defaultListen("guardcombat.storylets")}
        -> END
    
    = storylets
    { 
        - health < 10 && TURNS_SINCE(-> deathsdoor) < 0:
            -> deathsdoor
        - happiness > 80 && TURNS_SINCE(-> happiness3) < 0:
            -> happiness3
        - happiness > 70 && TURNS_SINCE(-> happiness2) < 0:
            -> happiness2
        - happiness > 60 && TURNS_SINCE(-> happiness1) < 0:
            -> happiness1
        - anger > 80 && TURNS_SINCE(-> anger3) < 0:
            -> anger3
        - anger > 70 && TURNS_SINCE(-> anger2) < 0:
            -> anger2
        - anger > 60 && TURNS_SINCE(-> anger1) < 0:
            -> anger1
    }
    

=== function listenEnemyHits(enemyHits, Knot)
    {listen(enemyHits, -1, -1, -1, -1, -1, -1, Knot, "", "", "", "", "", "")}
    
=== function listenPlayerHits(playerHits, Knot)
    {listen(-1, playerHits, -1, -1, -1, -1, -1, "", Knot, "", "", "", "", "")}
    
=== function listenEnemyParries(enemyParries, Knot)
    {listen(-1, -1, enemyParries, -1, -1, -1, -1, "", "", Knot, "", "", "", "")}
    
=== function listenPlayerParries(playerParries, Knot)
    {listen(-1, -1, -1, playerParries, -1, -1, -1, "", "", "", Knot, "", "", "")}
    
=== function listenEnemyDodges(enemyDodges, Knot)
    {listen(-1, -1, -1, -1, enemyDodges, -1, -1, "", "", "", "", Knot, "", "")}
    
=== function listenPlayerDodges(playerDodges, Knot)
    {listen(-1, -1, -1, -1, -1, playerDodges, -1, "", "", "", "", "", Knot, "")}
    
=== function listenTimer(timer, Knot)
    {listen(-1, -1, -1, -1, -1, -1, timer, "", "", "", "", "", "", Knot)}

=== function listenSameKnot(enemyHits, playerHits, enemyParries, playerParries, enemyDodges, playerDodges, Ltimer, Knot)
    {listen(enemyHits, playerHits, enemyParries, playerParries, enemyDodges, playerDodges, Ltimer, Knot, Knot, Knot, Knot, Knot, Knot, Knot)}

=== function listen(enemyHits, playerHits, enemyParries, playerParries, enemyDodges, playerDodges, Ltimer, eHitKnot, pHitKnot, eParryKnot, pParryKnot, eDodgeKnot, pDodgeKnot, tKnot) === 
    ~ COUNT_enemyHits = 0
    ~ COUNT_playerHits = 0
    ~ COUNT_enemyParries = 0
    ~ COUNT_playerParries = 0
    ~ COUNT_enemyDodges = 0
    ~ COUNT_playerDodges = 0
    ~ COUNT_timer = 0
    ~ LISTEN_enemyHits = enemyHits
    ~ LISTEN_playerHits = playerHits
    ~ LISTEN_enemyParries = enemyParries
    ~ LISTEN_playerParries = playerParries
    ~ LISTEN_enemyDodges = enemyDodges
    ~ LISTEN_playerDodges = playerDodges
    ~ LISTEN_timer = Ltimer

    ~ enemyHitsKnot = eHitKnot
    ~ playerHitsKnot = pHitKnot
    ~ enemyParriesKnot = eParryKnot
    ~ playerParriesKnot = pParryKnot
    ~ enemyDodgesKnot = eDodgeKnot
    ~ playerDodgesKnot = pDodgeKnot
    ~ timerKnot = tKnot
    
=== function defaultListen(Knot) ===
    {listenSameKnot(1, 1, 2, 2, 2, 2, 20, Knot)}
    # function Start_Combat
