function [total time] = prime(lower, upper)
%% PRIME returns the number of primes between lower and upper bounds

  total = 0;

  % start a timer to benchmark the main loop
  ticID = tic;

  for i = lower : upper
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
        total = total + 1;
    end

  end

  % stop the timer
  time = toc(ticID)

end