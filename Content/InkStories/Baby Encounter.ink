-> infant

=== infant ===
Hello, it's good to see you. It's been quite a while since I've had any visitors.


+ [Hello]
    -> hello
+ [You're... a baby]
    -> surprise


=== hello ===
What brings you to the shrine of the great whale? You're not here to kill me, are you?

+ [What? Why would I want to kill anyone?]
    -> killing
    
+ [I'm looking for information about the runes all over the temple.]
    -> babyrunes

+ [Can you tell me anything about the loop?]
    ->babytimeloop


=== surprise ===
Your observational skills are impressive.

+ ""
-> ending

=== killing ===
The last time anyone came to visit, they mentioned some kind of game and then stabbed me through with a sword. They were wearing the same clothing as you too.


=== babyhub ===
Is there anything else you wanted to talk about?

+ [What can you tell me about the time loop?]
    -> babytimeloop

+ [What can you tell me about the runes?]
    -> babyrunes

+ [What can you tell me about the history of the island]
    -> babyislandhistory
    
+ [I should be going (Leave)]
    -> babywait


=== babytimeloop ===
I can't tell you much. All I know is that at some point I started to recognize the passing of each day and the calamity that always follows.

+ [How long have you been Awoken?]
    -> babyawoken

=== babyawoken ===
Ah yes, Awoken is what they call it when you begin retaining your memories... I believe I've been "Awoken" for about 3700 years. The early years are kind of hazy, I was still just an infant after all, and it took me some time to learn to read well enough to educate myself through the shrine's library. By the time I had a consciousness capable of keeping track of the days, some indeterminate number of years had already passed.

+ [3700!? That's a long time]
    -> babylongtime
+ [Who do you mean by "they"?]
    -> babyvisitors
    
=== babylongtime ===
Yes, is has been quite lonely all these years, and there isn't much I can really do to pass the time given my infantile body.

+ [That sounds miserable, I'm sorry]
    -> babysavinggrace
+ [That's not so bad, social interraction is overrated and at least you can just relax all day]
    -> babynotsobad


=== babysavinggrace ===
It's alright I guess. Yes it can be quite dreary, but there is one saving grace.

+ [Which is?]
    -> babybooks
+ [Is it me visiting you?]
    -> babyno
    
=== babybooks ===
Books! The shrine holds an extensive library, mostly old stuffy religious texts, but also tomes of knowledge about the outside world, and wonderful tales of daring adventures or thrilling mysteries. I've learned pretty much all I know about the world through these books, they've made me who I am.

+ [There aren't nearly enough books in here to fill the space of 3700 years]
    ->babynotenoughbooks
    

=== babynotenoughbooks ===
True, I must have read each book hundreds of times over, memorizing each phrase, each 

=== babyrunes ===
The runes are simply an ancient version of the language we now speak. They are the written representation of the language our ancestors spoke centuries before the loop even started.

+ [So the runes on the temple are written by our ancestors?]
    -> babyancestorsrunes
    
=== babyancestorsrunes ===
Exactly. Some of them are prayers made out to the Great Whale, others are more utilitarian. For example, the ones carved above the door behind me translate to "restroom"

+ [Wait, you know how to read the runes?]
    -> babyreadrunes
    
=== babyreadrunes ===
Yes, it took me a long time to figure out at first, but the shrine's library holds texts written in the runish script and I was able to cross reference them with similar scripts using our modern alphabet. They use essentially the same alphabet as us, our characters have simply evolved over time to become more simple and streamlined.
+ [can you teach me?]
    -> babyteach
    
=== babyteach ===
I could... What exactly would you do with that information?

=== babyislandhistory ===
The history of the island is a bit fuzzy. Most of what I know has been gleaned from religeous texts and shrine records, so while I know some information, most of it relates to the shrine itself and the relgion practiced therin; information on the rest of the island is limited.

-> DONE

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
    

=== ending ===
-> END