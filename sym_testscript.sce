//Symphony Toolbox
//Script to test the toolbox
//Made by Keyur Joshi

//--------------
//initialization
//--------------

exec loader.sce

function performLotsOfTests(numVar)
	//be verbose
	mode(1)
	//get data
	sym_getNumVar
	sym_getNumConstr
	sym_getVarLower
	sym_getVarUpper
	sym_getObjCoeff
	sym_getObjSense
	for iter=0:(numVar-1)
		sym_isContinuous(iter)
		sym_isBinary(iter)
		sym_isInteger(iter)
	end
	sym_getNumElements
	sym_getMatrix
	sym_getConstrLower
	sym_getConstrUpper
	sym_getConstrRange
	sym_getConstrSense
	//solve the problem
	sym_solve
	//get more data
	sym_getStatus
	sym_isOptimal
	sym_isInfeasible
	sym_isAbandoned
	sym_isIterLimitReached
	sym_getIterCount
	sym_isTimeLimitReached
	sym_isTargetGapAchieved
	sym_getPrimalBound
	//these can fail if problem is infeasible
	try
		sym_getVarSoln
		sym_getObjVal
		sym_getConstrActivity
	catch
		mprintf("Some tests were skipped, most likely because the problem is infeasible.\n")
	end
endfunction

clc

//open environment
sym_open

//check that it is open
sym_isEnvActive

//misc. checks
sym_getInfinity

//---------------------------------------
//test 1: problem loader and data viewers
//---------------------------------------

//test 1 problem 1 : integer problem

//load the problem
sym_loadProblem(2,2,[0,0],[%inf,%inf],[1,1],[%t,%t],sym_maximize,sparse([1,2;2,1]),[-%inf;-%inf],[7;6.5])

performLotsOfTests(2)

//test 1 problem 2 : pure non-integer problem

//load the problem
sym_loadProblemBasic(2,2,[0,0],[%inf,%inf],[-1,-1],[%f,%f],sym_minimize,[1,2;2,1],[-%inf;-%inf],[7;6.5])

performLotsOfTests(2)

//test 1 problem 3 : infeasible problem

//load the problem
sym_loadProblem(2,1,[0.1,0.1],[0.9,0.9],[1,1],[%f,%t],sym_maximize,sparse([1,1]),[-%inf],[1])

performLotsOfTests(2)

//test 1 problem 4 : from https://people.richland.edu/james/ictcm/2006/3dsimplex.html
sym_loadProblemBasic(3,4,[0,0,0],[%inf,%inf,%inf],[20,10,15],[%f,%f,%f],sym_maximize,[3,2,5;2,1,1;1,1,3;5,2,4],[-%inf;-%inf;-%inf;-%inf],[55;26;30;57])

performLotsOfTests(3)

//test 1 problem 5 : same as problem 4, but constrainted to be integer
sym_loadProblemBasic(3,4,[0,0,0],[%inf,%inf,%inf],[20,10,15],[%t,%t,%t],sym_maximize,[3,2,5;2,1,1;1,1,3;5,2,4],[-%inf;-%inf;-%inf;-%inf],[55;26;30;57])

performLotsOfTests(3)

//test 1 problem 6 : from http://in.mathworks.com/help/optim/ug/mixed-integer-linear-programming-basics.html
sym_loadProblemBasic(8,3,[0,0,0,0,0,0,0,0],[1,1,1,1,%inf,%inf,%inf,%inf],[350*5,330*3,310*4,280*6,500,450,400,100],[%t,%t,%t,%t,%f,%f,%f,%f],sym_minimize,[5,3,4,6,1,1,1,1;5*0.05,3*0.04,4*0.05,6*0.03,0.08,0.07,0.06,0.03;5*0.03,3*0.03,4*0.04,6*0.04,0.06,0.07,0.08,0.09],[25;1.25;1.25],[25;1.25;1.25])

performLotsOfTests(8)

//test 1 problem 7 : unbounded solution
sym_loadProblemBasic(1,1,[0],[%inf],[1],[%t],sym_maximize,[1],[0],[%inf])

performLotsOfTests(1)

input("Test 1 complete. Press enter to clear console and perform next test.")

clc

//-------------------------
//test 2: problem modifiers
//-------------------------

//load a basic problem
sym_loadProblem(2,2,[0,0],[%inf,%inf],[1,1],[%t,%t],sym_maximize,sparse([1,2;2,1]),[-%inf;-%inf],[7;6.5])

sym_setObjSense(sym_minimize)
sym_getObjSense

sym_setContinuous(1)
sym_isContinuous(1)
sym_setInteger(1)
sym_isInteger(1)

sym_setObjCoeff(1,2)
sym_getObjCoeff
sym_setVarLower(1,-1)
sym_getVarLower
sym_setVarUpper(0,100)
sym_getVarUpper

sym_setConstrLower(0,-100)
sym_getConstrLower
sym_getConstrRange
sym_getConstrSense
sym_setConstrUpper(0,7.1)
sym_getConstrUpper
sym_getConstrRange
sym_getConstrSense
sym_setConstrType(1,"R",-1,6.6)
sym_getConstrLower
sym_getConstrUpper
sym_getConstrRange
sym_getConstrSense

sym_getNumVar
sym_getNumConstr

sym_addConstr(sparse([2,3]),"G",5)
sym_addConstr(sparse([1.5,2.3]),"E",7)
sym_getConstrLower
sym_getConstrUpper
sym_getConstrRange
sym_getConstrSense
sym_deleteConstrs([2,3])
sym_getNumVar
sym_getNumConstr

sym_addVar(sparse([1;1]),-%inf,%inf,1,%f,"test1")
sym_addVar(sparse([1.5;0.5]),100,200,-0.2,%t,"test2")
sym_getVarLower
sym_getVarUpper
sym_getObjCoeff
sym_isContinuous(2)
sym_isBinary(2)
sym_isInteger(2)
sym_isContinuous(3)
sym_isBinary(3)
sym_isInteger(3)
sym_getMatrix
sym_deleteVars([2,3])
sym_getNumVar
sym_getNumConstr

input("Test 2 complete. Press enter to clear console and perform next test.")

clc

//--------------------------
//test 3: runtime parameters
//--------------------------

//load a basic problem
sym_loadProblem(2,2,[0,0],[%inf,%inf],[1,1],[%t,%t],sym_maximize,sparse([1,2;2,1]),[-%inf;-%inf],[7;6.5])

sym_setDblParam("time_limit",10)
sym_getDblParam("time_limit")
sym_setStrParam("probname","testprob")
sym_getStrParam("probname")
sym_setIntParam("verbosity",1)
sym_getIntParam("verbosity")
sym_setIntParam("xyz",11)
sym_resetParams
sym_getDblParam("time_limit")
sym_getStrParam("probname")
sym_getIntParam("verbosity")

//------------
//finalization
//------------

//close environment
sym_close

//check that it has closed
sym_isEnvActive
