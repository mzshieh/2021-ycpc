private fun nextLine() = readLine()!!
private fun nextInt() = nextLine().toInt()
private fun nextToks() = nextLine().split(" ").filter{it.length>0}
private fun nextInts() = nextToks().map{it.toInt()}

fun String.runLength(): Int {
	var ret = 0
	var acc = 0
	for (i in 0 until this.length) {
		acc += 1
		if (i == this.length-1 || this[i] != this[i+1]) {
			ret += 1
			acc = 0
		}
	}
	return ret
}

fun main () {
	val (low, up) = nextInts()
    var s = low.toString(2)
	var last = s
	var ans = s.runLength().toLong()
    for (i in (low+1)..up) {
		val t = i.toString(2)
		if (last.endsWith("1")) ans -= 1
		ans += t.runLength()
		last = t
	}
	println("$ans")
}
