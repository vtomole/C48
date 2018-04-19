(define (count i st)
	   (if (null? st) i 
	       (count (+ i 1) (cdr st))))
(count 0 '(1 2 3 4 5))
 
