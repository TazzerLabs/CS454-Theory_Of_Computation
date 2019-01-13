
#include <stdio.h>
#include <iostream>
#include <gmpxx.h>
#include <string>

using namespace std;


//
string mmult(int B[][38], int n)
{
    
    // Set up the mpz_t arrays for matrix multiplication
    mpz_class X[1][38], Y[38][38], Z[38][1], S[1][38],
                resB[38][38], a[38][38];
    
    
    // Set matrixs to appropriate values/copying
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 38; j++) // Setting starting to all 0's
        {
            X[i][j] = 0;
        }
    }
    for (int i = 0; i < 38; i++) // copy of B
    {
        for (int j = 0; j < 38; j++)
        {
            Y[i][j] = B[i][j];
        }
    }
    for (int i = 0; i < 38; i++) // Copy of B
    {
        for (int j = 0; j < 38; j++)
        {
            a[i][j] = B[i][j];
        }
    }
    for (int i = 0; i < 38; i++) // Setting final to all 1's
    {
        for (int j = 0; j < 1; j++)
        {
            Z[i][i] = 1;
        }
    }
    // END OF Copying
    
    
    // Doing the Transition Matrix to the power of n
    // do n times
    while (n-- != 0)
    {
        
        // Set resB to all 0's
        for (int i = 0; i < 38; i++)
        {
            for (int j = 0; j < 38; j++)
            {
                resB[i][j] = 0;
            }
        }

        // Doing B * B and storing it in resB
        for (int i = 0; i < 1; i++)
        {
            
            for (int j = 0; j < 38; j++)
            {
                for(int k = 0; k < 38; k++)
                {
                    
                    //? += B[i][k] * B[k][j];
                    // after 1st iter, B^0,1,2,...,n-1 * B
                    resB[i][j] += a[i][k] * Y[k][j];
                    
                } // end of 3rd for
                
            } // end of 2nd for
            
        } // end of 1st for
        
        // Copy contents of res to a
        for (int i = 0; i < 38; i++)
            for (int j = 0; j < 38; j++)
                a[i][j] = resB[i][j];

    } // == END OF POWER
    
 
    
    // Set the Starting state in x and final state in Z
    X[0][0] = 1;
    Z[0][37] = 0;
    
    
    
    // Does the A * B Matrix multiplication
    for (int i = 0; i < 1; i++)
    {
        
        for (int j = 0; j < 38; j++)
        {
            for(int k = 0; k < 38; k++)
            {
                
                //S[i][j] += A[i][k] * (B[k][j])^n;
                S[i][j] += X[i][k] * a[k][j];
                
            } // end of 3rd for
            
        } // end of 2nd for
        
    } // end of 1st for
    
    
    // Generate new M and N based on S's dimensions
    // and C's dimensions *** Change for the new S matrix dims
    mpz_class Final[1][1];
    
    // Does the (A * (B)^n) * C Matrix multiplication
    for (int i = 0; i < 1; i++)
    {
        
        for (int j = 0; j < 1; j++)
        {
            
            for(int k = 0; k < 38; k++)
            {
                
                //Final[i][j] += A(B)^n[i][k] * C[k][j];
                Final[i][j] += S[i][k] * Z[k][j];
                
            } // end of 3rd for
            
        } // end of 2nd for
        
    } // end of 1st for
    
    
    // Returns the string of the Final 1x1 matrix
    return Final[0][0].get_str();
    
} // end of mmult