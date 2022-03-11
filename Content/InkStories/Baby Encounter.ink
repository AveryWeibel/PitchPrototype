-> babyintro

=== babyintro ===

    = start
    Hello, it's good to see you. It's been quite a while since I've had any visitors.
    
    
    + [Hello]
        -> hello
    + [You're... a baby]
        -> surprise


    = hello
    What brings you to the shrine of the Great Whale? You're not here to kill me, are you?
    
    + [What? Why would I want to kill you?]
        -> killing
        
    + [I'm looking for information about the runes all over the temple.]
        -> babyrunes
    
    + [Can you tell me anything about the loop?]
        ->babytimeloop


    = surprise
    Your observational skills are quite impressive.
    
    + [Sorry, I haven't had many conversations with babies before.]
    -> understand
    + [Thanks!]
    -> dummy
    + [Thanks (sarcastic)]
    -> so
    
    = understand
    I understand, it must be quite a surprise meeting a baby who is smarter than you.
    
    + [...]
    -> so
    + [That was rude]
    -> apologies
    
    = dummy
    You aren't the sharpest spear on the rack, are you?
    
    + [That was rude]
    -> apologies
    
    = apologies
    My apologies, you remind me of the last visitor I had, and they were quite terrible to me.
    
    + [I'm sorry to hear that]
    -> sorry
    + [Who was your last visitor?]
    -> lastvisitor
    + [What do you mean terrible?]
    -> killing
    
    = sorry
    It's okay, that was many cycles ago, and you seem to be kinder than him so far.
    
    + [I have some questions for you]
    -> babyhub
    
    = lastvisitor
    I'm not sure, he was wearing the same clothing as you though. He stabbed me through with a sword after mentioning some kind of game. He returned a couple times to kill me, eventually he stopped coming though. I guess he got bored or something.
    
    + [I have some questions for you]
    -> babyhub
    
    = so
    So... <>
    -> hello
    
    = killing
    The last time anyone came to visit, they mentioned some kind of game and then stabbed me through with a sword. They were wearing the same clothing as you too.

    + [I have some questions for you]
    -> babyhub
    
=== babyhub ===
What do you want to ask about?

+ [What can you tell me about the time loop?]
    -> babytimeloop

+ [What can you tell me about the runes?]
    -> babyrunes

+ [What can you tell me about the history of the island]
    -> babyislandhistory
    
+ [I should be going (Leave)]
    -> babywait


=== babytimeloop ===

    = start
    I can't tell you much. All I know is that at some point I started to recognize the passing of each day and the calamity that always follows.
    
    + [How long have you been Awoken?]
        -> awoken

    = awoken
    Ah yes, Awoken is what they call it when you begin retaining your memories... I believe I've been "Awoken" for about 3700 years. The early years are kind of hazy, I was still just an infant after all, and it took me some time to learn to read well enough to educate myself through the shrine's library. By the time I had a consciousness capable of keeping track of the days, some indeterminate number of years had already passed.
    
    + [3700!? That's a long time]
        -> longtime
    + [Who do you mean by "they"?]
        -> visitors
        
    = visitors
    Did I not mention that I've had a few visitors in the past? My contact with the outside world has been severely limited since I can't leave the shrine, but the few times I've met outsiders I tried to get as much info about the outside world as I could.
    
    + [It must get lonely being locked in here by yourself]
    ->longtime
    
    = longtime
    Yes, is has been quite lonely all these years, and there isn't much I can really do to pass the time given my infantile body.
    
    + [That sounds miserable, I'm sorry]
        -> savinggrace
    + [That's not so bad, social interraction is overrated and at least you can just relax all day]
        -> notsobad
        
    
    = notsobad
    Relaxing all day gets old after a thousand years. However, there is one saving grace.
    
    + [Which is?]
    -> books
    + [Is it me visiting you?]
    -> no


    = savinggrace
    It's alright I guess. Yes it can be quite dreary, but there is one saving grace.
    
    + [Which is?]
        -> books
    + [Is it me visiting you?]
        -> no
    
    = no
    No. It's books. <>
    -> library
    
    = books
    Books! <>
    -> library
    
    = library
    The shrine holds an extensive library, mostly old stuffy religious texts, but also tomes of knowledge about the outside world, and wonderful tales of daring adventures or thrilling mysteries. I've learned pretty much all I know about the world through these books.
    
    + [There aren't nearly enough books in here to fill the space of 3700 years]
        ->notenoughbooks
    

    = notenoughbooks
    True, I must have read each book hundreds of times over, memorizing each page, each phrase. I've dreamed of grand adventures of my own: vanquishing villains, saving the day, but most of all, seeing the world. Tell me, do you remember the beauty of a sunset? I've never seen one myself. Is it as stunning as the stories say?
    
    + [I've seen many sunsets, it's beautiful every time]
    -> beautiful
    + [I've seen many sunsets, it gets old eventually]
    -> getsold
    + [The world isn't as exciting as your stories make it out to be]
    -> excitingstories
    + [I can't remember.]
    -> cantremember
    
    = beautiful
    If we ever escape this endless purgatory, you must take me outside and show me.
    
    + [It would be my pleasure]
    -> thankyou
    + [I don't know what will happen when the loop ends but I will try]
    -> thankyou
    + [I have more questions]
    -> babyhub
    
    = getsold
    Perhaps... It's hard for me to imagine something so splendid 'getting old' after spending an eternity in this room. I've spent the centuries entertaining myself with nothing but my imagination. After this, I don't think seeing the sun could ever get old.
    
    + [I have more questions]
    -> babyhub
    
    = thankyou
    Thank you friend. Now, was there anything else you wanted to talk about?
    
    + [What can you tell me about the time loop?]
        -> babytimeloop
    
    + [What can you tell me about the runes?]
        -> babyrunes
    
    + [What can you tell me about the history of the island]
        -> babyislandhistory
        
    + [I should be going (Leave)]
        -> babywait
        
        
    = excitingstories
    Perhaps... Or perhaps it is, and you've taken for granted the beauty of the world around you. Try spending a couple hundred years in this room and see how exciting the outside world sounds by the end.
    
    + [I have more questions]
    -> babyhub   
    
    
    = cantremember
    I guess you and I are both in the dark. If you do happen to remember, please come tell me.
    
    + [I have more questions]
    -> babyhub
    + [I should be going (Leave)]
    -> babywait
    
    
=== babyrunes ===

    = runes
    The runes are simply an ancient version of the language we now speak. They are the written representation of the language our ancestors spoke centuries before the loop even started.
    
    + [So the runes on the temple are written by our ancestors?]
        -> ancestors
    
    = ancestors
    Exactly. Some of them are prayers made out to the Great Whale, others are more utilitarian. For example, the ones carved above the door behind me translate to "restroom"
    
    + [Wait, you know how to read the runes?]
        -> read
    
    = read
    Yes, it took me a long time to figure out at first, but the shrine's library holds texts written in the runish script and I was able to cross reference them with similar scripts using our modern alphabet. They use essentially the same alphabet as us, our characters have simply evolved over time to become more simple and streamlined.
    
    + [can you teach me?]
        -> teach
    
    = teach
    I could... What exactly would you do with that information?
    
    #+ [I'm not sure, I've just seen them around the island and wanted to see what they mean]
    #-> runesmeaning
    + [I'm hoping it could help me figure out what's causing the loop]
    -> wanttoknow
    + [The runes could be the key to ending the loop]
    -> endingtheloop
    
    = endingtheloop
    You... want to end the loop?
    
    + [Yes]
    -> loopfeelings
    + [Of course, don't you?]
    -> ofcourse
    + [I'm still undecided]
    -> undecided
    
    = undecided
    Please you must bring an end to this nightmare. <>
    -> loopfeelings
    
    = ofcourse
    Of course I do! <>
    -> loopfeelings
    
    = loopfeelings
    If we could break free of this cycle, I could finally see the sunset, feel its warmth on my skin for the first time. I could see the stars. I could... I could... I could travel the world. I could... I could do anything...
    
    + [Then you'll teach me how to read the runes?]
    -> yes
    
    
    = wanttoknow
    ...Are you certain you want to know what's causing the loop?
    
    + [Do you know the answer?]
    -> noidont
    + [Why wouldn't I?]
    -> because
    
    = because
    Because <>
    -> notthefirst
    
    = noidont
    No I don't, but <>
    -> notthefirst
    
    = notthefirst
    you're not the first person to come asking such questions. The last time I taught someone about the runes, I never saw them again. I guess whatever they were trying to do didn't work. That or they didn't like the answers they uncovered.
    
    + [Who came before me?]
    -> notsure
    + [I still want to know how to read the runes]
    -> fine
    
    = notsure
    I'm not sure what their name was. They wore the same clothing as you, but they were different from the one that kept killing me. Their mask looked like [description of the guard captain's mask which is not implemented yet].
    
    + [I still want to know how to read the runes]
    -> fine
    
    
    = yes
    Yes! But <>
    -> returntome
    
    = fine
    Fine, but <>
    -> returntome
    
    = returntome
    only on the condition that you return to me and tell me what you discover.
    
    + [Deal]
    -> deal
    + [Deal (lie)]
    -> deal
    #+ [I can't make any promises]
    #-> nopromises
    
    = deal
    Okay. [The baby proceeds to teach you to read the runes]
    
    + [I still have some questions for you]
    -> babyhub
    
    + [I should be going (Leave)]
    -> babywait
    

=== babyislandhistory ===

    = start
    The history of the island is a bit fuzzy. Most of what I know has been gleaned from religious texts and shrine records, so while I know some information, most of it relates to the shrine itself and the relgion practiced therin; information on the rest of the island is limited. [This conversation is still under development]

    + [I have more questions]
    -> babyhub

=== babywait ===
W-wait... could you stay just a bit longer? It's been so long since I've had company, and believe it or not, you're the best company I've had so far.

+ [Sure, what do you want to talk about? (in progress)]
    -> babywait
+ [No, I really do need to go]
    -> babyokaygo
    
=== babyokaygo ===
Okay, go if you must. But at least... come back soon okay? Promise me?
+ [I promise (Leave)]
    -> END
+ [I can't make any promises (Leave)]
    -> END
    