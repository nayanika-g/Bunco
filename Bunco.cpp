//
//  Bunco.cpp
//  Bunco
//
//  Created by Howard Stahl on 1/27/17.
//  Copyright © 2017 Howard Stahl. All rights reserved.
//

#include "Bunco.h"
#include <iostream>

namespace cs31
{
    Bunco::Bunco() : mRound( 0 )
    {
        
    }
    
    // stringify the game by stringifying the board
    std::string Bunco::display( std::string msg ) const
    {
        using namespace std;
        std::string s = mBoard.display();
        s = s + msg;
        
        if (gameIsOver())
        {
            if (determineGameOutcome() == TIEDGAME)
            {
                s = s + "\n\t\tBunco wound up tied!\n";
            }
            else if (determineGameOutcome() == HUMANWONGAME)
            {
                s = s + "\n\t\tyou won Bunco!\n";
            }
            else
            {
                s = s + "\n\t\tyou lost Bunco!\n";
            }
        }
        return( s );
    }
    
    // set the current round of play, notifying the board and each
    // player of the current round
    void Bunco::setRound( int round )
    {
        mRound = round;
        mBoard.setCurrentRound( round );
        mHuman.setRound(round);
        mComputer.setRound(round);
    }
    
    // TODO: let the human player play
    // when the amount is zero, the Die should be rolled for random play
    // when the amount is not zero, we are trying to cheat for testing
    // purposes.  in that case, this method should force a specific roll
    // amount.
    int Bunco::humanPlay( int amount )
    {
        int value = mHuman.roll(amount);
        
        if( amount == 0 ) {
            
            return value;
            
        }

        return( amount );
    }
    
    // TODO: let the computer player play
    // when the amount is zero, the Die should be rolled for random play
    // when the amount is not zero, we are trying to cheat for testing
    // purposes.  in that case, this method should force a specific roll
    // amount.
    int Bunco::computerPlay( int amount )
    {
        
        int value = mComputer.roll(amount);
        
        if( amount == 0 ) {
            
            return value;
            
        }
        
        return( amount );
        
    }
    
    // TODO: considering each player's score, determine the
    // winner of this round of play
    Bunco::ROUNDOUTCOME Bunco::determineRoundOutcome( ) 
    {
        ROUNDOUTCOME result = ROUNDOUTCOME::NOTDECIDED;
        
        bool hasAPlayerWonRound(false);
        
        //if scores are tied, neither player has won the round
        
        if( mHuman.getScore() > mComputer.getScore() ) {
            
            hasAPlayerWonRound = true;
            
            mBoard.markHumanAsWinner();
            
        }
        
        if( mComputer.getScore() > mHuman.getScore() ) {
            
            hasAPlayerWonRound = true;
            
            mBoard.markComputerAsWinner();
            
        }
        
        
        if(hasAPlayerWonRound) {
            
            if(mHuman.getScore() > mComputer.getScore()) {
                
                result = ROUNDOUTCOME::HUMANWON;
                
            }
            
            else {
                
                result = ROUNDOUTCOME::COMPUTERWON;
                
            }
            
            
        }
        
        //std::cerr << "computer score: " << mComputer.getScore() << std::endl;
        //std::cerr << "human score: " << mHuman.getScore() << std::endl;

        
        return( result );
        
    }
    
    // TODO: count up the number of won rounds by each player to determine
    // the game's outcome
    Bunco::GAMEOUTCOME  Bunco::determineGameOutcome( ) const
    {
        GAMEOUTCOME result = GAMEOUTCOME::GAMENOTOVER;
        
        int gameComputerWins = mBoard.countUpComputerRoundWins();
        int gameHumanWins = mBoard.countUpHumanRoundWins();
        
        //game is over when the computer and human have a cumulative score of 6
        
        bool finishedLastRound = (gameComputerWins + gameHumanWins == 6);
        
        if( finishedLastRound ) {
            
            if( gameComputerWins > gameHumanWins ) {
                
                result = GAMEOUTCOME::COMPUTERWONGAME;
                
            }
            
            else if( gameComputerWins < gameHumanWins ) {
                
                result = GAMEOUTCOME::HUMANWONGAME;
                
            }
            
            else {
                
                result = GAMEOUTCOME::TIEDGAME;
                
            }
            
        }
        
        
        //std::cerr << "computer total: " << mBoard.countUpComputerRoundWins() << std::endl;
        //std::cerr << "human total: " << mBoard.countUpHumanRoundWins() << std::endl;

        
        return( result );
        
    }
    
    // is the game over?
    bool Bunco::gameIsOver() const
    {
        GAMEOUTCOME result = determineGameOutcome();
        return( result != GAMENOTOVER );
    }

}
