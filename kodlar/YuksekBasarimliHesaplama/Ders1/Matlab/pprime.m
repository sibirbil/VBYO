function [total, time] = pprime(lower, upper)
%% PRIME returns the number of primes between lower and upper bounds
%% Parallel version

  % to store the sum for the local labindex:
  localsum = 0;

  % calculate the lower and upper bounds for this labindex
  % note: labindex goes from 1..n, unlike MPI rank which is 0-based
  chunksize = idivide(int32(upper-lower), numlabs);
  mylower = lower + ((labindex-1) * (chunksize+1));
  myupper = mylower + chunksize;

  % start a timer to benchmark the main loop
  ticID = tic;

  % loop over the local bounds
  parfor i = mylower : myupper
    isprime = 1; % TRUE

    if i <= 1
        isprime = 0; % FALSE
    elseif i == 2
        isprime = 1; % TRUE
    else
        for j = 2 : i-1
            if ( mod (i, j) == 0 )
                isprime = 0; %FALSE
            end
        end
    end

    if isprime == 1
        % here we increment just our local sum
        localsum = localsum + 1;
    end

  end

  % stop the timer
  time = toc(ticID)

  % update the global total based on all the localsums
  total = gplus(localsum);
end