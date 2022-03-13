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
VAR destinationKnot = ""

VAR timer = -1

-> spellcasterintro

=== spellcasterintro ===

    = start
    Who are you? What are you doing here?

    + [I could ask you the same thing (WIP)]
    -> start
    + [Name's Whale. Who are you? (WIP)]
    -> start
    + [Where are we?]
    -> where

    = where
    It seems we're in an extradimensional space
    
    + [How?]
    -> how
    
    = how
    This realm between realms exists due to the residual energy of what you islanders refer to as "The Great Whale". We are currently inside the physical manifestasion of that creature's spirit.
    
    + [I thought The Great Whale was dead]
    -> dead
    
    = dead
    It is dead. But a being of power this immense leaves something behind even after death. It seems your people understood that the energy of this creature has been "watching over" the island in a sense, even after death.
    
    + [Then what are you doing here?]
    -> savingthewhale
    
    = savingthewhale
    I am attempting to save The Great Whale's spirit. Something is causing it to leave this plane of existence, though I am not quite sure what it is or how to stop it.
    
    + [Then what is this spell you are casting?]
    -> spells
    
    = spells
    I've cast a variety of spells, mostly to measure the energy of The Whale and help determine what exactly is going on. However, the spell you see before you [pretend there are visual effects] is designed to rewind time, as it appears I will not have enough time to figure out how to contain the spirit before its departure.
    
    + [So you're what's causing the loop]
    -> whatloop
    
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
    
    = notpossible
    No... that's... not possible... Could it be some flaw in the spell? No... No I refuse to believe it, you must be lying.
    
    + [You must end your spell]
    -> doomed
    
    = doomed
    If I end the spell, we are doomed.
    
    + [What do you mean?]
    -> tsunamicause
    
    = tsunamicause
    As The Whale's spirit prepares to leave this realm, its power swells. Like the dying of a star, the very end of its life cycle will culminate in a massive explosion of energy.
    
    + [The tsunami...?]
    -> tsunamicause2
    
    = tsunamicause2
    Yes, in our physical world, such a massive surge of spiritual energy might manifest in the form of a natural catastophe: storms, tsunamis, volacanic eruptions, etc. If I end my spell, calamity will be unleashed upon the island.
    
    + [So even if the loop ends, everyone will die...]
    -> decision
    
    
=== decision ===

    = start
    ...
    
    + [I need to talk to the other islanders about this...]
    -> leave
    + [The loop still needs to end]
    -> areyousure
    + [The loop can't end]
    -> sotruebestie
    
    = sotruebestie
    So you won't get in my way?
    
    + [I guess not]
    -> ending
    
    = ending
    [THIS IS ONE ENDING]
    
    + [cool]
    -> END
    
    = areyousure
    You would let your entire village perish without even trying to stop this calamity?
    
    + [cool justification 1]
    -> timetofight
    + [cool justification 2]
    -> timetofight
    + [cool justification 3]
    -> timetofight
    
    = timetofight
    I guess I have to choice but to stop you by force then.
    
    + [So be it (attack)]
    # function Start_Combat
    ->END
    
    = leave
    Okay, see you tomorrow.
    
    + [Goodbye (leave)]
    -> END
    
    
=== function defaultListen(Knot) ===
{listen(1, 1, 2, 2, 4, 5, 20, Knot)}
# function Start_Combat

=== function listen(enemyHits, playerHits, enemyParries, playerParries, enemyDodges, playerDodges, Ltimer, Knot) === 
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
    ~ destinationKnot = Knot
    
