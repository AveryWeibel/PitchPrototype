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

-> guardcaptainintro

=== guardcaptainintro ===

    = start
    If you're here, that means you've finally decided to join us, Whale. It's good to have you back.
    
    + [Back from where?]
    ->unawoken
    
    = unawoken
    Before, you were Unawoken, which means you weren't really a person.
    
    + [What do you mean?]
    -> unawokenmeaning
    
    = unawokenmeaning
    The Unawoken are static. They are cursed to repeat the same mistakes every day, unable to change. They aren't free like us.
    
    + [Are we free?]
    -> enoughtalk
    
    = enoughtalk
    Enough talk, it's time I gave you a proper welcome to the loop [this section needs to be expanded]
    
    + [...]
    # function Start_Combat
    -> END
    
    