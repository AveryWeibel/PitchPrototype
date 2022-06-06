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

VAR health = 150

VAR happiness = 50
VAR fear = 50
VAR anger = 50

VAR startingKnot = "spellcasterintro"

#destinationKnots 
VAR enemyHitsKnot = ""
VAR playerHitsKnot = ""
VAR enemyParriesKnot = ""
VAR playerParriesKnot = ""
VAR enemyDodgesKnot = ""
VAR playerDodgesKnot = ""
VAR timerKnot = ""
VAR destinationKnot = ""

-> spellcasterintro

=== spellcasterintro ===

    = start
    Who are you? What are you doing here?

    + [I could ask you the same thing]
    -> samething
    + [Name's Whale. Who are you?]
    -> nameis
    + [Where are we?]
    -> where



    = samething
    I'm here because I am trying to preserve a great spiritual power that resides here. Ah but that's beside the point. I didn't think there was anyone on this island who could still read the old runes; tell me, how did you get in here?
    
    + [A talking baby taught me to read]
    -> insane
    + [I know how to read runes]
    -> huh
    + [None of your business]
    -> business
    
    
    
    = insane
    Ah, I see you are insane. Apologies, but could you please leave me to my devices? I'm doing some very important work that your feeble mind clearly would not comprehend.
    
    + [(Snarky response)]
    -> insane
    + [Who are you?]
    -> nameis
    + [Where are we?]
    -> where
    
    
    
    = huh
    Huh... Well, no matter. Could you please leave me alone? I'm quite busy.
    
    + [Who are you?]
    -> nameis
    + [Where are we?]
    -> where
    
    
    
    = business
    I understand. Well if you could leave me be, that would be much appreciated.
  
    + [Who are you?]
    -> nunya
    + [Where are we?]
    -> nunya
    
    
    
    = nunya
    None of your business.
    
    + [Touché]
    -> touche
    + [Answer me!]
    -> ugh
    + [...]
    -> dot
    
    
    = touche
    Yes, well you can leave me alone now.
    
    + [Who are you?]
    -> ugh2
    + [Where are we?]
    -> ugh3
    
    
    
    
    
    = ugh
    Ugh fine, since you don't seem to be leaving any time soon. What do you want to know?
    
    + [Who are you?]
    -> nunya
    + [Where are we?]
    -> nunya
    
    
    
    
    
    = dot
    ...
    
    + [Who are you?]
    -> ugh2
    + [Where are we?]
    -> ugh3
    
    
    
    
    
    = ugh2
    Ugh. <>
    -> nameis
    
    
    
    
    = ugh3
    Ugh. <>
    -> where
    
    
    = nameis
    You may call me Tempus, I study the spiritual and the arcane. As you can imagine, the spirit of your Great Whale is of some importance to me.
    
    + [Where are we?]
    -> where
    + [Need another dialogue option here]
    -> nameis
    + [Potentially even another dialogue option here]
    -> nameis
    
    
    
    
    = where
    It seems we're in an extradimensional space.
    
    + [What does that even mean?]
    -> whatmean
    + [How?]
    -> how
    + [Cool.]
    ->takingwell
    
    
    
    
    
    
    = takingwell
    You seem to be taking this rather well all things considered.
    
    + [I've seen a lot weird stuff recently, I've learned to roll with it.]
    -> weirdstuff
    + [No sense in freaking out about it.]
    -> freakingout
    + [Can we get back to the topic at hand?]
    -> botheringme
    
    
    
    
    
    
    
    = freakingout
    Really? Most people would see this kind of revelation as worth "freaking out about".
    
    + [Not me.]
    -> weirdstuff
    + [Most people are lame.]
    -> weirdstuff
    + [I've seen a lot weird stuff recently, I've learned to roll with it.]
    -> weirdstuff
    
    
    
    
    
    
    = botheringme
    Where were we? Ah yes, you were bothering me and interrupting my work.
    
    + [What do you mean we're in an "extradimensional space"?]
    -> whatmean
    + [How does this place exist?]
    -> how
    
    
    
    
    
    
    = weirdstuff
    Intriguing... Well if you wouldn't mind leaving me alone, I have some work to attend to...
    
    + [What kind of work?]
    -> savingthewhale
    + [Did you make this place?]
    -> makethisplace
    + [Why are we in an "extradimensional space"?]
    -> how
    
    
    
    
    
    = whatmean
    It means we are in a world that is separate from our own. A sort of pocket realm maybe... 200 meters in diameter.
    
    + [Did you make this place?]
    -> makethisplace
    + [How does this place exist?]
    -> how
    
    
    
    
    = makethisplace
    No. <>
    -> how
    
    
    
    
    
    = how
    This realm between realms exists due to the residual energy of what you islanders refer to as "The Great Whale". We are currently inside the physical manifestasion of that creature's spirit.
    
    + [The Great Whale is a living creature?]
    -> dead
    + [This doesn't make any sense.]
    ->nosense
    + [We're inside a whale?]
    -> insidewhale
    
    
    
    
    
    
    = nosense
    I don't expect you to understand. While your people know the Great Whale is powerful, your knowledge of the spiritual and arcane is... primitive at best.
    
    + [The Great Whale is a living creature?]
    -> dead
    + [We're inside a whale?]
    -> insidewhale
    
    
    
    
    
    
    = insidewhale
    Not <italics>a</> whale, <italics>the</> whale. The guardian deity of this island. And we aren't <italics>literally</> inside it.
    
    + [The Great Whale is a living creature?]
    -> dead
    
    
    
    
    
    
    = dead
    No, it's dead. But a being of power this immense leaves something behind even after death. It seems your people understood that the energy of this creature has been "watching over" the island in a sense.
    
    + [Then what are you doing here?]
    -> savingthewhale
    + [What do you mean "watching over"?]
    -> religion
    + [Did you kill it?]
    -> killit

    
    
    
    
    = religion
    Well, it's your religion, not mine. I'm sure the islanders believe it has something to do with protection from bad weather, blessings of bountiful food, that sort of thing. A spiritual presence this immense would certainly scare off any malicious spirits, so perhaps it's true that it protects the island in a way.
    
    + [What are you doing here?]
    -> savingthewhale
    + [Did you kill the whale?]
    -> killit
    
    
    
    
    
    = killit
    Me? Kill the Great Whale? There's no way I could accomplish something like that, nor would I want to. No, this majestic creature died a long, long time ago. Its spirit has been residing here since, which is why I'm confused as to what has suddenly changed.
    
    + [What are you doing here?]
    -> savingthewhale
    + [Need another dialogue option here]
    -> killit
    
    
    
    
    
    = savingthewhale
    I am attempting to save The Great Whale's spirit. Something is causing it to leave this plane of existence, though I am not quite sure what it is or how to stop it.
    
    + [Then what is this spell you are casting?]
    -> spells
    + [You're keeping its spirit trapped here?]
    -> trapped
    + [Where is it going?]
    -> going
    
    
    
    
    
    
    = trapped
    Trapped? I'm trying to save it, preserve it. Not only for the simple principle of the conservation of nature and its spirits, but for the benefit of your island.
    
    + [Then what is this spell you are casting?]
    -> spells
    + [How noble of you (WIP)]
    -> trapped
    + [Benefit of the island? (WIP)]
    -> trapped
    
    
    
    
    
    = going
    Your guess is as good as mine. The next life? The great beyond? The void? All I know is that I must prevent it from leaving.

    + [Then what is this spell you are casting?]
    -> spells
    + [You're keeping its spirit trapped here?]
    -> trapped
    
    
    

    
    
    
    = spells
    I've cast a variety of spells, mostly to measure the energy of The Whale and help determine what exactly is going on. However, the spell you see before you [pretend there are visual effects] is designed to rewind time.
    
    + [So you're causing the loop]
    -> whatloop
    + [Why would you want to do that?]
    -> notenoughtime
    + [You need to end your spell]
    -> whywouldi
    
    
    
    
    
    = notenoughtime
    It appears I will not have enough time to figure out how to contain the spirit before its departure. I'm just using this trick to buy myself maybe a few days or weeks to figure out a solution.
    
    + [So you're causing the loop]
    -> whatloop
    + [You need to end your spell]
    -> whywouldi
    
    
    
    
    
    = whywouldi
    What? Why would I do that?
    
    + [You've trapped the island in a time loop for centuries.]
    -> notpossible
    + [May add another dialogue option here]
    -> whywouldi

    
    
    
    
    = whatloop
    Loop? What loop? This is my first time casting this spell, I just need a bit more time to figure out how to prevent the spirit from dissapearing.
    
    + [Oh no... You're not Awoken]
    -> explain
    + [No, the island has been trapped in a loop for centuries.]
    -> notpossible
    
    
    
    
    
    = explain
    What? Explain yourself. What do you mean by "Awoken"?
    
    + [It's what we call people who retain their memories between loops. The island has been trapped in your time loop for a very long time]
    -> notpossible
    + [It doesn't matter. (WIP)]
    -> explain
    + [How can you not know? It's your spell. (WIP)]
    -> explain
    
    
    
    = notpossible
    No... that's... not possible... Could it be some flaw in the spell? No... No I refuse to believe it, you must be lying.
    
    + [You must end your spell.]
    -> doomed
    + [Why would I lie?]
    -> idk
    + [Then you are a fool.]
    -> noyou
    
    
    
    
    
    = idk
    I... I don't know... Maybe you want the island to be destroyed. That's why you've been trying to get me to end the spell...
    
    + [Why would I want to destry the island I live on?]
    -> options
    + [You don't really believe that do you?]
    -> options
    + [Do you have any idea how ridiculous you sound?]
    -> options
    
    
    
    
    
    = options
    It doesn't matter... Even if what you say is true, it doesn't change the fact that is is the only way to save the island from destruction.
    
    + [destruction?]
    -> tsunamicause
    
    
    
    
    
    = noyou
    Say what you will, this is the only way to save the island from destruction.
    
    + [destruction?]
    -> tsunamicause
    
    
    
    
    
    
    = doomed
    If I end the spell, we are doomed.
    
    + [What do you mean?]
    -> tsunamicause
    
    
    
    
    
    = tsunamicause
    As The Whale's spirit prepares to leave this realm, its power swells. Like the dying of a star, the very end of its life cycle will culminate in a massive explosion of energy.
    
    + [The beam of light...?]
    -> tsunamicause2
    + [what will that energy do?]
    -> destruction
    
    
    
    
    
    = destruction
    Such a massive surge of energy would probably obliterate the island.
    
    + [So if the loop ends, everyone will die...]
    -> decision
    
    
    
    
    
    = tsunamicause2
    Yes, in our physical world, such a massive surge of spiritual energy might manifest in such a form. If I end my spell, calamity will still be unleashed upon the island.
    
    + [So if the loop ends, everyone will die...]
    -> decision
    
    
=== decision ===

    = start
    ...
    
    + [I need to talk to the other islanders about this...]
    -> leave
    + [The loop still needs to end]
    -> areyousure
    * [The loop can't end]
    -> sotruebestie
    
    
    
    
    
    = sotruebestie
    You seemed so sure just a moment ago.
    
    + [It's not worth the deaths of all of the islanders]
    -> understanding
    + [We have an eternity to figure out how to end the loop safely, there must be a way.]
    -> eternity
    + [Maybe the loop can be saved from the cycle of blood it's been stuck in. (WIP)]
    -> sotruebestie
    
    
    
    
    
    = eternity
    Understand that what you are proposing is a risk. Could you drink the ocean with a thimble, even if you had an eternity? There's no guarantee that we will ever contain the Great Whale, even with all the time in the world. 
    
    + [Do you want the loop to continue or not?]
    -> risk
    + [We have to try.]
    -> understanding
    + [Then what are you still doing here?]
    -> musttry




    = musttry
    I've been aware of the risks from the start. Still I must do what I can to contain the spirit of the whale. I can't simply give up without even trying.
    
    + [You have already been trying for centuries.]
    -> perhaps
    + [When does it end? When do we decide when it's time to give up?]
    -> up2u
    
    
    
    = up2u
    I suppose that's up to you for the time being. You may at any point in the future change your mind and come back to end the loop if you so choose. Though I must warn you that if I am still "Unawoken" then you will encounter similar resistance as you have today.
    
    + [What about if you Awaken?]
    -> strength
    + [Okay.]
    -> understanding
    
    
    = strength
    Then it comes down to the strength of my spirit and how long I can continue on trying to find a solution. I could still very well never figure it out, it may be impossible. It could also be the case that it will only take a couple weeks once I am Awoken.
    
    + [Okay, I understand]
    -> understanding
    + [I've changed my mind]
    -> start
    
    
    
    
    
    = perhaps
    Perhaps what you say is true. But if you yourself have recently Awoken, isn't it possible that I could Awaken some time in the future? I have used the spell in the past, I can only assume I was unknowingly stuck in a loop until my Awawkening on those previous occasions. So please, allow me to at least try.
    
    + [Okay.]
    -> understanding
    + [I've changed my mind.]
    -> start
    
    
    
    
    = risk
    I wish to continue with my spell. I'm only asking because this is a risk I have been aware of from the beginning. If you accept this risk and still wish to try then we are in agreement. If not...
    
    + [I accept the risk.]
    -> understanding
    + [I've changed my mind.]
    -> start
    
    
    
    = understanding
    Then we've reached an understanding. The loop will continue indefinitly, until we can find a way out where everyone lives. I trust that until that time, you will do what you can to ensure the loop is peaceful. [THIS IS ONE ENDING]
    
    + [cool]
    -> END
    
    
    
    = areyousure
    You would let your entire village perish without even trying to stop this calamity?
    
    + [It appears stopping the calamity is beyond both our abilities.]
    -> timetofight
    + [The island has lived in this bloody cycle for years, I don't see the state of the island improving.]
    -> timetofight
    + [The alternative is to simply wait and hope that, maybe centuries from now, a solution magaically presents itself.]
    -> timetofight
    
    
    
    
    
    
    = timetofight
    I guess I have no choice but to stop you by force then.
    
    + [So be it (attack)]
    # function Start_Combat
    ->END
    
    
    
    
    = leave
    Okay, see you tomorrow.
    
    + [Goodbye (leave)]
    -> END
    
    
=== tempuscombat ===

    = storylets
    { 
        - health < 10 && TURNS_SINCE(-> deathsdoor) < 0:
            -> deathsdoor
        - anger > 90 && TURNS_SINCE(-> anger4) < 0:
            -> anger4
        - anger > 80 && TURNS_SINCE(-> anger3) < 0:
            -> anger3
        - anger > 70 && TURNS_SINCE(-> anger2) < 0:
            -> anger2
        - anger > 60 && TURNS_SINCE(-> anger1) < 0:
            -> anger1
        - else:
            {defaultListen("guardcombat.storylets")}
            -> END
    }
    
    = anger1
    I'm sure you imagine yourself the hero, saving the island from being trapped for eternity.
    
    + [Yes I do because that's the truth.]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [You have no idea the amount of suffering you've caused, do you?]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [...]
        {defaultListen("tempuscombat.storylets")}
        -> END
    
    = anger2
    I know you are trying to do the right thing, and for that you've earned my respect. But, you are sending the island to its doom.
    
    + [I'm saving the island from prolonged suffering.]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [You have my respect as well, it's a shame to have to kill you.]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [...]
        {defaultListen("tempuscombat.storylets")}
        -> END
        
    = anger3
    Stubborn fool. An eternity will be over in the blink of an eye for those who are Unawoken.
    
    + [What will be left of our village after an eternity? A couple of innocent survivors amoungst a crowd of mad murders?]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [And for the Awoken? How long will they toil and suffer?]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [...]
        {defaultListen("tempuscombat.storylets")}
        -> END
        
        
    = anger4
    ...
    
    + [Nothing left to say?]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [Please, let's end this peacefully.]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [...]
        {defaultListen("tempuscombat.storylets")}
        -> END
        
    = difference
    What difference does it make? If you get your way we will both die.
    
    + [I'd rather not have to kill you myself.]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [Fine, prepare to die.]
        {defaultListen("tempuscombat.storylets")}
        -> END
    + [...]
        {defaultListen("tempuscombat.storylets")}
        -> END
    
    = deathsdoor
    <red>*cough* I've said all I needed to say... You know what will happen if you kill me. I've never feared death, I only regret that I wasn't able to preserve the whale spirit and save these people from destruction. Now go on... Get on with it.</>
    
    + [(continue)]
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
    {listenSameKnot(1, 1, 2, 2, 2, 2, 20, Knot)}
    # function Start_Combat
