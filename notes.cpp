// 1:-Redux Concepts:-
// What is Redux:-
//     Redux ek library hai and
//     Redux ek pattern hai jisme sequence me chizo ko kiya jata hai.
//     rect me reducer bhi pattern par kaam kart hai
//     fully independent Frameworks hai(not bounded with react)
//         redux ko kahi par bhi use kiya ja sakta hai(frontend, backend, Mobail App)

// Why use Redux:-
//     add photo 1:-
//     Lifting State se hum previous problem solve karte hai tab vo problem solve jati hai but new problem create bhi ho jati us problem ka naam props drilling hota hai.
//     jab hum ek component se dusare component me state ko pass karte hai by using of props(state->pehle-->parent component me jayega -->fir-> target components me) tab props banti jati hai usa problem ka naam props drilling hota hai.
//     us problem ko avoid karne ke liya hum Redux ka use karte hai or koi global state management ka.

//     add photo:-2
//     add photo:-3
//     Global State rahe uske sath-sath access kahi se bhi kar paye globale  state ko tabhi props ko avoid kar sakte completelly.
//     kyuki jab Global State parent par hoga tab child components tak jane ke kiya props tab bhi use hoga vo bhi props drilling create kar dega usko avoid karne ke liya global state access har jagh hona chahiya.

// conclusion:- props drilling ko avoid karne ke liya hum redux ka use karte hai.
//             redux me global state ko har jagah se access kar sakte hai.
//             koi component se Global state ko bhi change kar sakte hai.
//             global state ko hi redux me store bola jata hai

// middleware:-
//     node.js me middleware request par lagta hai.
//     redux me middleware action par lagta hai. 
// reducer:- ek function hota  hai jisme previous state aur koi action pass karte hai aur new state return karta hai.

// When to use Redux:-
//     Big Applications
//     High Frequency of State Changes

// install:-
//     npm init -y
//     npm install redux
//     write in pkg.json:- "type": "module",

// 3 Principle of redux:-
//     1:- Global state hona chahiya
//     2:- State ko directly change na kre:- Immutable update
//     3:- reducer should be pure

// index.js:-
    import {createStore} from 'redux';

    // store
    const store =  createStore(reducer);

    // reducer
    function reducer(state={amount:1},action) {
        if (action.type === 'increment') {
            // mutability:- state ko directly change nahi karna hai
            // state.amount = state.amount +1; :-wrrong way--> but output is same 
            
            // immutability:- 
            return {amount: state.amount+1}  // right way
        }
        return state;
    }

    // global state:- 
    console.log(store.getState()); // reducer function call hoga 

    // dispatch with action:-
    store.dispatch({type:'increment'})
    console.log(store.getState());

// Middleware with redux, PayLoad and Action Creators:- 
//     install any middleware:- npm install redux-logger
//     logger middleware sabhi action aur state ko dikhata hai
//     kud ka middleware bhi banna sakte hai

// index.js:-
    import {createStore, applyMiddleware} from 'redux';
    import logger from 'redux-logger';

    // store
    const store =  createStore(reducer,applyMiddleware(logger.default));

    // reducer
    function reducer(state={amount:1},action) {
        // multiple action:-
        if (action.type === 'increment') {
            // immutability:- 
            return {amount: state.amount+1}
        }
        if (action.type === 'decrement') {
            // immutability:- 
            return {amount: state.amount-1}
        }
        if (action.type === 'incrementByAmount') {
            // immutability:- 
            return {amount: state.amount + action.payload}
        }
        return state;
    }

    // Action Creators:-
    function increment() {
        return {type:'increment'}
    }

    setInterval(()=>{
        store.dispatch(increment())
    },2000)

    // setInterval(()=>{
    //     store.dispatch({type: 'decrement'})
    // },2000)

    // setInterval(()=>{
    //     store.dispatch({type: 'incrementByAmount',payload:4})
    // },2000)

// conclusion:- Write way to write all these:-
// index.js:-
    import {createStore, applyMiddleware} from 'redux';
    import logger from 'redux-logger';

    // action name constants
    const inc = 'increment';
    const dec = 'decrement';
    const incByAmt = 'incrementByAmount';

    // store
    const store =  createStore(reducer,applyMiddleware(logger.default));

    // reducer
    function reducer(state={amount:1},action) {
        // multiple action:-
        if (action.type === inc) {
            // immutability:- 
            return {amount: state.amount+1}
        }
        if (action.type === dec) {
            // immutability:- 
            return {amount: state.amount-1}
        }
        if (action.type === incByAmt) {
            // immutability:- 
            return {amount: state.amount + action.payload}
        }
        return state;
    }

    // Action Creators:-
    function increment() {
        return {type:inc}
    }

    function decrement() {
        return {type:dec}
    }

    function incrementByAmount(value) {
        return {type:incByAmt, payload:value}
    }

    // setInterval(()=>{
    //     store.dispatch(increment())
    // },2000)

    // setInterval(()=>{
    //     store.dispatch(decrement())
    // },2000)

    setInterval(()=>{
        store.dispatch(incrementByAmount(4))
    },2000)

// Thunk Middleware:-
// make fake REST API server:- Redux se koi link nahi hai.
// suppose database hai db.json me
// install:- npm i -g json-server
//     add:- "start": "json-server db.json"
//     start:- npm start
//     npm install axios

// What is Redux-Thunk-Middleware:-
// Action Creators synchronous hote hai wait nahi karta aur yahi problem hai.
// async, await nahi use kar sakte.
// problem hai ki API ka data aane tak Action Creators ko wait karwana padega bina async, await use kiya bina.
// usi problem ko fix karta hai Redux-Thunk Middleware.
// Redux-Thunk Middleware:- dispatch ko wait run karane me help karta hai Redux-Thunk Middleware
// install :- npm install redux-thunk

// Note:- make sure api dusare tarminal par run ho rah ho.
// db.json;-
    {
        "accounts":[
            {"id":1, "amount":200},
            {"id":2, "amount":100}
        ]
    }

// Without dynamic id:-
// index.js:-
    import {createStore, applyMiddleware} from 'redux';
    import logger from 'redux-logger';
    import axios from 'axios';
    import thunk from 'redux-thunk';

    // action name constants
    const init = 'init';
    const inc = 'increment';
    const dec = 'decrement';
    const incByAmt = 'incrementByAmount';

    // store
    const store =  createStore(reducer,applyMiddleware(logger.default, thunk.default));

    // reducer
    function reducer(state={amount:1},action) {
        // multiple action:-
        switch(action.type)
        {
            case init:
                // jo API se aaye ga vo amount me aa jayega 
                return {amount: action.payload};
            case inc:
                return {amount: state.amount+1};
            case dec:
                return {amount: state.amount-1}
            case incByAmt:
                return {amount: state.amount + action.payload};
            default:
                return state;
        }
    }

    // Async API Calling:-
        // Fake API se data aa raha hai aur vo init vale reducer me jayega
        // API  bhi run karo sath me:- db.json

    // Action Creators:-
    async function getUser(dispatch,getState) // async Action Creators
    {
        const {data} = await axios.get('http://localhost:3000/accounts/1')
        dispatch(initUser(data.amount))
    }

    function initUser(value) {  // sync Action Creators(getUser function se dispatch ho raha hai)
        return {type:init, payload:value};
    }

    function increment() {
        return {type:inc}
    }

    function decrement() {
        return {type:dec}
    }

    function incrementByAmount(value) {
        return {type:incByAmt, payload:value}
    }

    setTimeout(()=>{
        store.dispatch(getUser) // 2 action ho raha hai and 2 dispatch
    },3000)

// With dynamic id:-
// index.js:-
    import {createStore, applyMiddleware} from 'redux';
    import logger from 'redux-logger';
    import axios from 'axios';
    import thunk from 'redux-thunk';

    // action name constants
    const init = 'init';
    const inc = 'increment';
    const dec = 'decrement';
    const incByAmt = 'incrementByAmount';

    // store
    const store =  createStore(reducer,applyMiddleware(logger.default, thunk.default));

    // reducer
    function reducer(state={amount:1},action) {
        // multiple action:-
        switch(action.type)
        {
            case init:
                // jo API se aaye ga vo amount me aa jayega 
                return {amount: action.payload};
            case inc:
                return {amount: state.amount+1};
            case dec:
                return {amount: state.amount-1}
            case incByAmt:
                return {amount: state.amount + action.payload};
            default:
                return state;
        }
    }

    // Async API Calling:-
        // Fake API se data aa raha hai aur vo init vale reducer me jayega
        // API  bhi run karo sath me:- db.json

    // Action Creators:-
    function getUser(id) // async Action Creators
    {
        return async(dispatch,getState)=>{
            const {data} = await axios.get(`http://localhost:3000/accounts/${id}`)
            dispatch(initUser(data.amount))
        }
    }

    function initUser(value) {  // sync Action Creators(getUser function se dispatch ho raha hai)
        return {type:init, payload:value};
    }

    setTimeout(()=>{
        store.dispatch(getUser(1)) // 2 action ho raha hai  
    },3000)
// **************************************
// Multiple Reducer:- very important
// index.js:-
    import {createStore, applyMiddleware, combineReducers} from 'redux';
    import logger from 'redux-logger';
    import axios from 'axios';
    import thunk from 'redux-thunk';
    /* ---------------------------------- */

    // action name constants
    // const init = 'account/init';
    const inc = 'account/increment';
    const dec = 'account/decrement';
    const incByAmt = 'account/incrementByAmount';
    const incBonus = 'bonus/increment';
    const getAccUserPending = 'account/getUser/pending';
    const getAccUserFulfilled = 'account/getUser/fulfilled';
    const getAccUserRejected = 'account/getUser/rejected';

    /* ---------------------------------- */
    // store
    // Imp:- global state dono reducer ke combination se banne ga
    // bas reducer nahi pass hoga combine reducer pass hoga
    const store =  createStore(combineReducers({
        account: accountsReducer,
        bonus: bonusReducer
    }),applyMiddleware(logger.default, thunk.default));

    /* ---------------------------------- */
    // reducer:- 1
    function accountsReducer(state={amount:1},action) {
        // multiple action:-
        switch(action.type)
        {
            case getAccUserFulfilled:
                return {amount: action.payload, pending:false};
            case getAccUserRejected: // rejected hoga tab amount ko kuch nahi hoga aur error aa jaye ga
                return {...state, error: action.error, pending:false};
                case getAccUserPending:
                    return { ...state,pending:true };
            case inc:
                return {amount: state.amount+1};
            case dec:
                return {amount: state.amount-1}
            case incByAmt:
                return {amount: state.amount + action.payload};
            default:
                return state;
        }
    }
    // reducer:- 2
    function bonusReducer(state={points:0},action) {
        switch (action.type) {
            case incBonus:
                return {points: state.points + 1};
            case incByAmt:
                // action.payload vo amount hai jo 100 se jada hoga tabhi +1 hoga
                if(action.payload>=100)
                    return {points: state.points + 1};
            default:
                return state;
        }
    }

    /* ---------------------------------- */
    // Action Creators:- 1 sabhi function Action Creators hai but ek action se refect ho kar sub-action banna rahe hai 
    function getUserAccount(id) // async Action Creators
    {   
        
        return async (dispatch,getState)=>{
            try{
                dispatch(getAccountUserPending());
                const {data} = await axios.get(`http://localhost:3000/accounts/${id}`);
                dispatch(getAccountUserFulFilled(data.amount));
            }catch(error){
                dispatch(getAccountUserRejected(error.message));
            }
        }
    }
    function getAccountUserFulFilled(value) {  // sync Action Creators(getUser function se dispatch ho raha hai)
        return {type:getAccUserFulfilled, payload:value};
    }
    function getAccountUserRejected(error) {  // sync Action Creators(getUser function se dispatch ho raha hai)
        return {type:getAccUserRejected, error:error};
    }
    function getAccountUserPending(value) {  // sync Action Creators(getUser function se dispatch ho raha hai)
        return {type:getAccUserPending};
    }

    // Action Creators:- 2
    function increment() {
        return {type:inc}
    }

    // Action Creators:- 3
    function decrement() {
        return {type:dec}
    }

    // Action Creators:- 4
    function incrementByAmount(value) {
        return {type:incByAmt, payload:value}
    }

    // Action Creators:- 5
    function incrementBonus() {
        return {type:incBonus};
    }
    /* ---------------------------------- */
    // call by using dispatch:-
    setTimeout(()=>{
        // 2 id hai json data me 
        store.dispatch(getUserAccount(2)) // 2 action ho raha hai and 2 dispatch
    },3000)

    // <------ya dono reducer me hai condition check kar raha hai------>
    // amount update hoga aur point dono update hoga condition se hisab se
    // setTimeout(()=>{
    //         store.dispatch(incrementByAmount(200))
    // },3000)

    // setTimeout(()=>{ // bouns update hoga
    //     store.dispatch(incrementBonus())
    // },2000)

    // setInterval(()=>{
    //     store.dispatch(increment())
    // },2000)

    // setInterval(()=>{
    //     store.dispatch(decrement())
    // },2000)

    /* ---------------------------------- */

// photo:- 4

// 2:-Redux with React:-
// suppose subscribe karna ek task hai:-
// redux ka dispatch --> view me call hoga
// dispatch se action call hoga subscribe
// action se state change hogi subscribed ho jayega

// react-redux library:- redux ki state ko react ko samjhana ki react apni state ki tarah hi maano vo react-redux librarey karta hai.

// photo:- 5
// Note:- jis parent component par store rahe ga uske child component sabhi acces kar paye gaye.

// photo:- 6
// Note:- useSelector hook ki help se store ko kahi se bhi access kar paye gaye.

// photo:- 7
// Note:- useDispatch se hum log wapas se store ki state ko change kar sakte hai.

// Note:-
//     jaisa hum jante hai ki lifting up state se code complex ho jata hai aur new problem create ho jati hai.
//     usi problem ko fix karta hai redux.

// how fix props Drilling problem:-
// install:- npx create-react-app .
//         sudo npm install -g json-server
//         npm install axios
//         npm install redux --> store banane ke liya index.js(store as prop jayega)
//         npm install redux-thunk --> middleware
//         npm install redux-logger --> middleware
//         npm install react-redux --> redux ka state link kar dega react se. 
// create folder and file in src:-
//     1:- actions--> index.js
//     2:- components--> Account.js, Bonus.js
//     3:- reducers--> account.js, bonus.js

// db.json:-

// Actions Folder:-
//     index.js:- paste code.

// components Folder:-
//     Account.js:- paste code
//     Bonus.js:-paste code

// reducers Folder:-
//     account.js:- paste code
//     bonus.js:- paste code

// outer App.js:- paste code
// app.css:- paste code
// outer index.js:- paste code
// index.css:-paste code

// for code run:- --> make sure both are run in different port
//     db.json:- json-server db.json -p 8000
//     rect run:- go dir:- npm start

// 2:54:-
*************************************

// 3:-Redux ToolKit(RTK) With React:-
// install:-
//     npm install @reduxjs/toolkit 
//     npm install react-redux
// slice ke andar reducers hoga aur usme hi action create hoga.
// copy slice code from this link and do changes:- https://redux-toolkit.js.org/tutorials/quick-start#install-redux-toolkit-and-react-redux 
// Make Folder and File:-
//     slices:- accountSlice.js, bonusSlice.js
//     components:- Account.js, Bonus.js Reward.js
//     reducers:- reward.js

// db.json:-

// slices:- 
// accountSlice.js:-

// bonusSlice.js:-

// components:-
// Account.js:-

// Bonus.js:-

// Reward.js

// reducers:-
// reward.js:-

// outer App.js:-
// outer index.js:-
// app.css:-
// index.css:-

// for code run:- --> make sure both are run in different port
//     db.json:- json-server db.json -p 8000
//     react run:- go dir:- npm start

// revise

// 4:-RTK Query With React:-
// RTK Query:- ya redux tool kit ki interface Query hai
ya optionanl hai agar thunk ya koi aur middleware use kar rahe hai tab
RTK Query spacially API fatching ke liya acha hai.
RTK Query me bahut sare inbuild feature(caching, polling..etc) hai jo thunk se nahi ho paye gaye.
caching:- ka matlab:- agar ek bar API ko call kar lia hai to fir se API call karne ke liya Network par nahi jaye ga. vo cache se hi response lekar aayega.
RTK Query ki help se hum log directly data faching Hooks banna sakte hai jisme hum logo ko useSelecter, useDispatch use karne ki jarurt nahi hai.


// 5:-Project with RTK Async Thunk:-


// 6:-Redux Saga:-

