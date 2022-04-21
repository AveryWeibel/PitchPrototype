VAR canReadRunes = 0
VAR doorOpen = 0

-> readdoor

=== readdoor ===

    {canReadRunes == 0:
        There seem to be words on this cave, but you can't seem to read them.
    - else:
        The runes shine brightly back at you.
    }
    
    + [Inspect]
        -> inspectdoor
        
    + {canReadRunes == 1 && doorOpen == 0} [Read the runes]
        ->opendoor
        
    + {canReadRunes == 1 && doorOpen == 1} [Unread the runes]
        ->closedoor
        
    + [(Leave)]
        -> END
        
    = inspectdoor
    These seems to be runes carved into the cave walls. You wonder if anyone knows how to read them.
        -> DONE
    
    = opendoor
    The door begins to open.
        ~ doorOpen = 1
        # function Open_Door
        ->END
    
    = closedoor
    The door begins to close.
        ~ doorOpen = 0
        # function Open_Door
        ->END