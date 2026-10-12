


function MakeGamePlayer(name, totalscore, gamesplayed) 
{
  // Define desired object
  var obj = { name        : name        ,
              totalscore  : totalscore  ,
              gamesplayed : gamesplayed
            };

  // Return it
  return obj;
}


function main()
{
  var obj1 = MakeGamePlayer("Pepe", 1000, 10);

  var obj2 = DevTest_Func1("Pepe", 1000, 10);

  Console_Printf("Name: %s, higscore: %d, ngames: %d \n", obj1.name, obj1.totalscore, obj1.gamesplayed);

  Console_Printf("Name: %s, higscore: %d, ngames: %d \n", obj2.name, obj2.totalscore, obj2.gamesplayed);  
}

