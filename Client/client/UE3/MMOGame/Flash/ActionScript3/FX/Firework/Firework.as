/*
 * FLINT PARTICLE SYSTEM
 * .....................
 * 
 * Author: Richard Lord
 * Copyright (c) Richard Lord 2008-2011
 * http://flintparticles.org/
 * 
 * Licence Agreement
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

package ActionScript3.FX.Firework
{
	import ActionScript3.org.flintparticles.common.actions.Age;
	import ActionScript3.org.flintparticles.common.actions.Fade;
	import ActionScript3.org.flintparticles.common.counters.Blast;
	import ActionScript3.org.flintparticles.common.displayObjects.Dot;
	import ActionScript3.org.flintparticles.common.easing.Quadratic;
	import ActionScript3.org.flintparticles.common.events.EmitterEvent;
	import ActionScript3.org.flintparticles.common.initializers.*;
	import ActionScript3.org.flintparticles.twoD.actions.*;
	import ActionScript3.org.flintparticles.twoD.emitters.Emitter2D;
	import ActionScript3.org.flintparticles.twoD.initializers.*;
	import ActionScript3.org.flintparticles.twoD.zones.DiscZone;

	import flash.geom.Point;

	public class Firework extends Emitter2D
	{
		public function Firework()
		{
			counter = new Blast( 50 );
			
			//addInitializer( new SharedImage( new Dot( 2 ) ) );
			addInitializer(new ImageClass(Test_ParClass) );
			addInitializer( new ColorInit( 0xFFFFFF00, 0xFFFF6600 ) );
			addInitializer( new Velocity( new DiscZone( new Point( 0, 0 ), 200, 120 ) ) );
			addInitializer( new Lifetime( 5 ) );
			addInitializer( new ScaleImageInit(0.1, 0.2) );
			
			addAction( new Age( Quadratic.easeIn ) );
			addAction( new Move() );
			addAction( new Fade() );
			addAction( new Accelerate( 0, 150 ) );
			addAction( new LinearDrag( 0.5 ) );
			
			addEventListener( EmitterEvent.EMITTER_EMPTY, restart, false, 0, true );
		}
		
		public function restart( ev:EmitterEvent ):void
		{
			start();
		}
	}
}