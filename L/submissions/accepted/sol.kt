private fun nextLine() = readLine()!!
private fun nextToks() = nextLine().split(" ").filter{it.length > 0}
private fun nextLongs() = nextToks().map{it.toLong()}

private fun runs(x: String) =
    x.mapIndexed{i, c -> if (i==0 || c!=x[i-1]) 1 else 0}.sum()

private fun runs(x: Long) = runs(x.toString(2))

fun Long.log2() = this.toBigInteger().bitLength() - 1

fun pre(x: Long): Long {
    if (x < 0L) return 1                     // take care of b = 0
    if (x < 2L) return x+1                   // terminal case
    val y = x + 1
    val lowbit = y.and(-y)
    if (y == lowbit)                         // x is in the form: 11...111
        return pre(x / 2) + y.log2() * y / 4
    if (lowbit == 1L)                        // x is in the form: 1?...??0
        return pre(x-1) + runs(x) - 1
    val z = y - lowbit                       // x is in the form: 1?...?011...1
    return pre(z - 1) + runs(z) * lowbit + (lowbit.log2()-1) * lowbit / 2
}

fun main() {
    val (b, e) = nextLongs()
    println("${pre(e) - pre(b - 1) + 1 - (b%2)}")
}
