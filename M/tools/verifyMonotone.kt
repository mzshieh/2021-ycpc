import kotlin.system.exitProcess
import java.io.File
import java.math.BigInteger

fun testIf(pred: Boolean, msg: String) {
    if (!pred) throw Exception(msg)
}

typealias Point = Pair<BigInteger,BigInteger>

private fun nextLine() = readLine()!!
private fun nextInt() = nextLine().toInt()
private fun nextToks() = nextLine().split(" ").filter{it.length in 1..15}
private fun nextBigs() = nextToks().map{it.toBigInteger()}
private fun nextPoint(): Point {
    val bigs = nextBigs()
	testIf(bigs.size == 2, "Not a point")
	return Pair(bigs[0], bigs[1])
}

// Minus
operator fun Point.minus(p: Point): Point {
    return Pair(first-p.first, second - p.second)
}
// Cross product
operator fun Point.times(p: Point): BigInteger {
    return first * p.second - second * p.first
}

fun verify(input: List<String>, answer: List<String>) {
    println("${input.size} ${answer.size}")
	val n = input[0].toInt()
	val pts = (1..n).map{nextPoint()}
	for (i in 1 until n-1) {
        val p = pts[i] - pts[i-1]
		val q = pts[i+1] - pts[i]
		testIf(p.first > BigInteger.ZERO, "Not increasing")
		testIf(q.first > BigInteger.ZERO, "Not increasing")
		testIf(q * p > BigInteger.ZERO, "Not convex")
	}
	testIf(readLine() == null, "Trailing data")
}

fun main(args: Array<String>) {
    try{
        verify(File(args[0]).readLines(), File(args[1]).readLines())
    } catch (e: Exception) {
        println(e)
		println("Wrong Answer")
        exitProcess(43)
    }
	println("Correct")
    exitProcess(42)
}
