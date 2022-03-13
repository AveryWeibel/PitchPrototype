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

#destinationKnots 
VAR enemyHitsKnot = ""
VAR playerHitsKnot = ""
VAR enemyParriesKnot = ""
VAR playerParriesKnot = ""
VAR enemyDodgesKnot = ""
VAR playerDodgesKnot = ""
VAR timerKnot = ""
VAR destinationKnot = ""

#otherNPC variables
VAR otherNPCVariable = -1

#my Variables
VAR endStory = false

Once upon a time...

 * There were two choices.
 * There were four lines of content.

- They lived happily ever after.
~ endStory = true
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