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