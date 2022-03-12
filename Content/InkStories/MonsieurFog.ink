# this is a global tags
# another tag
# wtf
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
VAR otherNPCVariable = 1

VAR fogs_string_mood = "good"
VAR fogs_current_mood = 1
EXTERNAL test()

->start

=== start ===
- I looked at Monsieur Fogg
# function fuck_david_coulson
*   ... and I could contain myself no longer.
    'What is the purpose of our journey, Monsieur?' {otherNPCVariable > 0: "penis" | "fuck" }
    ~ fogs_string_mood = "excellent"
    # function why
    ~ fogs_current_mood = 2
    'A wager,' he replied. 
    # function penis
    # timer 5
    * *     'A wager!'[] I returned.
            # function hateful
            # function yesdaddy
            He nodded. 
            * * *   'But surely that is foolishness!'
            * * *  'A most serious matter then!'
            - - -   He nodded again.
            TODO: Write this properly
            * * *   'But can we win?'
                    'That is what we will endeavour to find out,' he answered.
                    ~ fogs_string_mood = "good"
                    ~ fogs_current_mood = 1
            * * *   'A modest wager, I trust?'
                    'Twenty thousand pounds,' he replied, quite flatly.
            * * *   I asked nothing further of him then[.], and after a final, polite cough, he offered nothing more to me. <>
    * *     'Ah[.'],' I replied, uncertain what I thought.
    - -     After that, <>
*   ... but I said nothing[] and <> 
- we passed the day in silence
- -> END

=== fuck ===
pens hate this
-> END

=== function say_yes_to_everything ===
    ~ return true

=== function lerp(a, b, k) ===
    ~ return ((b - a) * k) + a
    
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