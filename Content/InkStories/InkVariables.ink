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

# function Start_Combat