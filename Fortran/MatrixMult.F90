program multtest
!Comparison of computation time for various fortran functions

implicit none
integer, parameter :: n = 300 
integer :: clockrate,clock_start,clock_end
real, dimension(n,n) :: a,b,c !array dimensions must be declared as such
real :: it, dt, mt,ni,nd,nm,d1,d2

!Establishes base time for element-wise dot product 
CALL system_clock(clock_start)
c = ijk(n,a,b)
CALL system_clock(clock_end)
it = (clock_end-clock_start)/REAL(clockrate)
print *, "ijk time: ", it
ni = maxval(c)

!column-row wise dot product
CALL system_clock(clock_start)
c = dot_prod(n,a,b)
CALL system_clock(clock_end)
dt = (clock_end-clock_start)/REAL(clockrate)
print *, "dot product time: ",dt
nd = maxval(c)

!Built in matrix-multiplication function
CALL system_clock(clock_start)
c = matmul(a,b)
CALL system_clock(clock_end)
mt = (clock_end-clock_start)/REAL(clockrate)
print *, "matmul time:", mt
nm = maxval(c)

d1 = nd - ni
d2 = nm - ni
print *, d1
Print *, d2

contains 

function ijk(n,a,b)!Computes matrix multiplication in the most tedious way possible
    implicit none

    integer, intent(in) :: n
    integer :: i,j,k
    real :: s
    real, dimension(n,n), intent(in) :: a,b
    real, dimension(n,n) :: ijk

!I am personally injured by these vectors starting at 1, but thats fortran 
    do i = 1, n
        do j = 1 , n
        s = 0
            do k = 1 , n
                s = s + a(i,k) * b(k,j)
                ijk(i,j) = s
            end do
        end do 
    end do 
end function

function dot_prod(n,a,b)!More intuative function that uses built in dot product for corresponding rows/columns
    implicit none

    integer :: i,j
    integer, intent(in) :: n
    real, dimension(n,n), intent(in) :: a,b
    real, dimension(n,n) :: dot_prod


    do i = 1, n
        do j = 1,n
            dot_prod(i,j) = dot_product(a(i,:),b(:,j))
        end do
    end do
end function

end program
