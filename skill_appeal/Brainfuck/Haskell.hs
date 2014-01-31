{-# OPTIONS -Wall -Werror #-}
import System.Environment
import qualified Data.ByteString.Lazy as BSL
import qualified Data.ByteString as BS
import Data.Word
 
data Bf = Input | Output | CurInc | CurDec | PtrDec | PtrInc | Loop [ Bf ]
data Memory = Memory [ Word8 ] Word8 [ Word8 ]
 
main :: IO ( )
main = do
    ( filename : _ ) <- getArgs
    code <- readFile filename >>= ( return . inputFilter ) >>= ( return . parseBf )
    input <- BS.getContents
    return ( execBf code ( BS.unpack input ) ) >>= ( return . BSL.pack ) >>= BSL.putStr
 
inputFilter :: [ Char ] -> [ Char ]
inputFilter = filter ( ` elem ` "[],.<>-+" )
 
parseBf :: [ Char ] -> ( [ Bf ] , [ Char ] )
parseBf ( ',' : xs ) = ( Input : l , r ) where
    ( l , r ) = parseBf xs
parseBf ( '.' : xs ) = ( Output : l , r ) where
    ( l , r ) = parseBf xs
parseBf ( '<' : xs ) = ( CurDec : l , r ) where
    ( l , r ) = parseBf xs
parseBf ( '>' : xs ) = ( CurInc : l , r ) where
    ( l , r ) = parseBf xs
parseBf ( '-' : xs ) = ( PtrDec : l , r ) where
    ( l , r ) = parseBf xs
parseBf ( '+' : xs ) = ( PtrInc : l , r ) where
    ( l , r ) = parseBf xs
parseBf ( '[' : xs ) = ( Loop l1 : l , r ) where
    ( l1 , r1 ) = parseBf xs
    ( l , r ) = parseBf r1
parseBf ( ']' : xs ) = ( [ ] , xs )
parseBf xs = ( [ ] , xs )
 
execBf :: ( [ Bf ] , [ Char ] ) -> [ Word8 ] -> [ Word8 ]
execBf ( xs , _ ) input = case execBfHelper xs ( Memory [ ] 0 [ 0 , 0 .. ] , input , [ ] ) of
    ( _ , _ , res ) -> reverse res
 
execBfHelper :: [ Bf ] -> ( Memory , [ Word8 ] , [ Word8 ] ) -> ( Memory , [ Word8 ] , [ Word8 ] )
execBfHelper ( Input : xs ) ( mem , ( h : input ) , output ) = execBfHelper xs ( ( inputMemory mem h ) , input , output )
execBfHelper ( Output : xs ) ( mem , input , output ) = execBfHelper xs ( mem , input , ( outputMemory mem ) : output )
execBfHelper ( CurDec : xs ) ( mem , input , output ) = execBfHelper xs ( ( curDec mem ) , input , output )
execBfHelper ( CurInc : xs ) ( mem , input , output ) = execBfHelper xs ( ( curInc mem ) , input , output )
execBfHelper ( PtrDec : xs ) ( mem , input , output ) = execBfHelper xs ( ( ptrDec mem ) , input , output )
execBfHelper ( PtrInc : xs ) ( mem , input , output ) = execBfHelper xs ( ( ptrInc mem ) , input , output )
execBfHelper ( Loop bf : xs ) env = case execBfHelper bf env of
    ( memory @ ( Memory _ 0 _ ) , input , output ) -> execBfHelper xs ( memory , input , output )
    env' -> execBfHelper ( Loop bf : xs ) env'
execBfHelper [ ] env = env
execBfHelper _ env = env
 
inputMemory :: Memory -> Word8 -> Memory
inputMemory ( Memory a1 _ a3 ) word = Memory a1 word a3
 
outputMemory :: Memory -> Word8
outputMemory ( Memory _ a2 _ ) = a2
 
curDec :: Memory -> Memory
curDec ( Memory ( a1H : a1 ) a2 a3 ) = Memory a1 a1H ( a2 : a3 )
curDec _ = Memory  [ ] 0  [ 0 , 0 .. ]
 
curInc :: Memory -> Memory
curInc ( Memory a1 a2 ( a3H : a3 ) ) = Memory ( a2 : a1 ) a3H a3
curInc _ = Memory  [ ] 0  [ 0 , 0 .. ]
 
ptrDec :: Memory -> Memory
ptrDec ( Memory a1 a2 a3 ) = Memory a1 ( pred a2 ) a3
 
ptrInc :: Memory -> Memory
ptrInc ( Memory a1 a2 a3 ) = Memory a1 ( succ a2 ) a3
