#combat variables
VAR LISTEN_enemyHits = -1
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

VAR health = 100

VAR happiness = 50
VAR fear = 50
VAR anger = 50

VAR startingKnot = "guardcaptainintro"

#destinationKnots 
VAR enemyHitsKnot = ""
VAR playerHitsKnot = ""
VAR enemyParriesKnot = ""
VAR playerParriesKnot = ""
VAR enemyDodgesKnot = ""
VAR playerDodgesKnot = ""
VAR timerKnot = ""
VAR destinationKnot = ""

-> guardcaptainintro

=== guardcaptainintro ===

    = start
    If you're here, that means you've finally decided to join us, Whale. It's good to have you back.
    
    + [It's good to be back]
    -> back
    
    + [Back from where?]
    ->unawoken
    
     
    = back
    That's the spirit! Are you excited for your new life in the loop?
    
    + [Yeah, it's going to be so fun!]
    -> fun
    + [No.]
    -> rude
    + [What's causing the loop?]
    -> questions
    + [Why is everyone dead? What happened?]
    -> questions
    
    
    = rude
    You will see it my way eventually. <>
    -> smile
    
    = fun
    I like your enthusiasm! In that case it's time give you a proper welcome to the loop. Are you ready to do battle?
    
    + [Bring it on!]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Why do all of my friends want to murder me?]
    -> friends
    + [I'd rather not.]
    -> toobad
    
    
    
    = friends
    This is what the loop is all about: the thrill and glory of conquest.
    
    + [Couldn't it be about something more pleasant?]
    -> pleasant
    + [The slaughter of innocent unarmed villagers is hardly glorious]
    -> slaughter
    + [Yes, bring me glory!]
        {defaultListen("guardcombat.storylets")}
        -> END
        
        
    = pleasant
    Early in the loop we would eat, drink, and party all day. The only thing that has stood the test of time has been the rush of battle. Come, I'll show you.
    
    + [Bring it on!]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Why do all of my friends want to murder me?]
    -> friends
    + [I'd rather not.]
    -> toobad    
    
    
    = slaughter
    They died because they were weak. Besides, they will not remember their suffering in the morning.
    
    + [You will still carry the weight of their suffering with you.]
    -> enoughtalk
    + [Is their remembrance of the suffering what makes your actions immoral?]
    -> enoughtalk
    
    = toobad
    Too bad, prepare yourself.
    
    + [Fine.]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [...]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Can't we just talk this out?]
        {defaultListen("guardcombat.storylets")}
        -> END
        
    
    
    = questions
    Ah, I'm sure you have a lot of questions. Don't worry, it will all become clear soon. Has Smile explained our game to you? <>
    -> smile
    
    
    = smile
    Has Smile explained our game to you?
    
    + [He tried to murder me.]
    -> murder
    + [Yeah something like that.]
    -> alreadyexplained
    + [No not really.]
    -> thekillinggame
    + [Who?]
    -> smile2
    
    
    = smile2
    The man with the blue mask and the ridiculous grin.
    
    + [He tried to murder me.]
    -> murder
    + [He explained your game.]
    -> alreadyexplained
    + [He didn't really explain anything.]
    -> thekillinggame
    
    = thekillinggame
    Smile, the fool... The game is simple. We compete to see who can get more kills. I always win. It's fair game to kill each other, but I usually let Smile have his fun first. Now that you're here, I suppose the game will get even more interesting.
    
    + [Sounds fun!]
    -> fun
    + [Sounds horrible.]
    -> horrible
    + [You're really messed up huh.]
    -> messedup
    
    = horrible
    You don't understand. <>
    -> pleasant
    
    
    = messedup
    Some may see it that way, perhaps they are right. Over a century spent in the loop changes you. Maybe one day you'll come to see my perspective as enlightened.
    
    + [You're insane.]
    -> enoughtalk
    + [I don't think I will.]
    -> shutup
    + [Maybe.]
    -> maybe
    + [...]
    -> shutup
    
    = maybe
    Well, it's time to give you a proper welcome to the loop.
    
    + [Bring it on!]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Why do all of my friends want to murder me?]
    -> friends
    + [I'd rather not.]
    -> toobad    
    + [...]
        {defaultListen("guardcombat.storylets")}
        -> END
    
    = alreadyexplained
    Great! then it's time for me to welcome you to the loop as well.
    
    + [Bring it on!]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Why do all of my friends want to murder me?]
    -> friends
    + [I'd rather not.]
    -> toobad
    + [...]
        {defaultListen("guardcombat.storylets")}
        -> END
    
    = murder
    Hah! Then it sounds like you know what the game is about already. In that case it's time give you a proper welcome to the loop. Are you ready to do battle?
    
    + [Bring it on!]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Why do all of my friends want to murder me?]
    -> friends
    + [I'd rather not.]
    -> toobad
    
    
    
    = unawoken
    Before, you were Unawoken, which means you weren't really a person.
    
    + [I don't really know what you mean but that already sounds insane.]
    -> unawokenmeaning
    
    + [What does that mean?]
    -> unawokenmeaning
    
    = unawokenmeaning
    The Unawoken are static. They are cursed to repeat the same mistakes every day, unable to change. They aren't free like us.
    
    + [Maybe we're the ones who are cursed.]
    -> deep
    
    + [Are we free?]
    -> enoughtalk
    
    = deep
    Ohoh so very deep Whale. You always were a bit pretentious.
    
    + [Shut up.]
    -> shutup
    + [We are stuck in an endless loop, surely it gets old.]
    -> endless
    
    
    = endless
    No. The rush, the thrill, the feeling of power. Those are eternal. Come, I'll show you.
    
    + [Bring it on!]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Why do all of my friends want to murder me?]
    -> friends
    + [I'd rather not.]
    -> toobad    
    
    
    = shutup
    Very well. It seems the time for talk is over. Prepare yourself.
    
    + [Bring it on!]
        {defaultListen("guardcombat.storylets")}
        -> END
    + [Why do all of my friends want to murder me?]
    -> friends
    + [I'd rather not.]
    -> toobad
    
    = enoughtalk
    Enough talk, it's time I gave you a proper welcome to the loop [this section needs to be expanded]
    
    + [...]
    # function Start_Combat
    -> END
    
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
    {listenSameKnot(1, 1, 2, 2, 4, 5, 20, Knot)}
    # function Start_Combat