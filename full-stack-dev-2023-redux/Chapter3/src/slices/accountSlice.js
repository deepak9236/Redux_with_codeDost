import { createSlice, createAsyncThunk } from '@reduxjs/toolkit';
import axios from 'axios';

const initialState = {
  amount: 10,
};

export const getUserAccount = createAsyncThunk(
  'account/getUser',
  async (userId, thunkAPI) => {
    const { data } = await axios.get(
      `http://localhost:8080/accounts/${userId}`
    );
    return data.amount;
  }
);

export const accountSlice = createSlice({
  name: 'account', // naam hi action bane ga
  initialState,
  reducers: {
    increment: (state) => {
      state.amount += 1; // immer-library
      // mutating jaisa lg raha hai code(state.amount += 1;) but hota nahi hai kyuki immer-library use kar rahe hai
      // immer-library:- copy banna leta hai.. immutable bannane ke liya 
    },
    decrement: (state) => {
      state.amount -= 1;
    },
    incrementByAmount: (state, action) => {
      state.amount += action.payload;
    },
  },
  extraReducers: (builder) => {
    builder
      .addCase(getUserAccount.fulfilled, (state, action) => {
        state.amount = action.payload;
        state.pending = false;
      })
      .addCase(getUserAccount.pending, (state, action) => {
        state.pending = true;
      })
      .addCase(getUserAccount.rejected, (state, action) => {
        state.error = action.error;
      });
  },
});

// Action creators are generated for each case reducer function
export const { increment, decrement, incrementByAmount } = accountSlice.actions;

export default accountSlice.reducer;
