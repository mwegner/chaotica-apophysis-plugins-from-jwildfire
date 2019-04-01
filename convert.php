<?php

/**

This is a pretty nutty script.  And don't worry--I realize it's crazy.  It's the kind of thing you have to write
in one evening, uninterrupted, because once the big decisions are made it becomes really hard to change.

The goal here is to take all of the compatible variations from JWildfire and transmogrify them into c/c++ plugins
for use in Chaotica.  Originally, I was just bringing over a few, and then I wanted to normalize the names so I
could paste directly JW -> Chaotica.  And then I just said, whatever, I'll start writing a script.

To be honest, it became a fun learning experience to dig into the failed corner cases.  So right now:

- All variations are converted (skipping DrawFunc)
- The contents of another directory are copied in replacing things

These replacements sometimes the original C, if it was easier to go that, or maybe converted scripts with manual
adjustments.

I really haven't commented this much, so, uh, enjoy.

Also, if you happen to find this elsewhere:  This is absolutely NOT a generic Java -> C convert.  I didn't even
look around if such a thing exists, because this is very domain-specific (I solved some issues by extending the
C side of the plugin stuff).


- Matthew / mwegner @ a bunch of places (gmail/twitter/etc)
*/

$files = glob('C:\Users\Matthew\Downloads\JWildfire-master/src/org/jwildfire/create/tina/variation/*.java', GLOB_BRACE);
foreach($files as $file)
{
    $headers = "";
    $headersNeedVectors = false;
    $replacements = array();
    $replacements['%java%'] = basename($file);
    $java = file_get_contents($file);

    // some global token replacements before we get started
    $java = str_replace('new DoubleWrapper()', '0.0', $java);
    $java = str_replace('DoubleWrapper', 'double', $java);

    $java = str_replace('new doubleWF()', '0.0', $java);
    $java = str_replace('doubleWF', 'double', $java);
    


    $original = explode("\n", $java);
    $lines = explode("\n", $java);

    // get the transform block (really could've moved this to a regular expression, I guess, but whatever)
    $transform = "";
    $capture = false;
    foreach($lines as $line)
    {
        $line .= "\n";

        if($line == "  }\n")
        {
            $capture = false;
        }

        if($capture)
        {
            $transform .= $line;
        }

        if($line == "  public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {\n")
        {
            $capture = true;
        }
    }

    // same for init/calc block
    $init = "";
    $capture = false;
    foreach($lines as $line)
    {
        $line .= "\n";

        if($line == "  }\n")
        {
            $capture = false;
        }

        if($capture)
        {
            $init .= $line;
        }

        if($line == "  public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {\n")
        {
            $capture = true;
        }
    }

    // try to match all xml names for variables
    if(preg_match('/public\sString\sgetName\(\)\s{[\s\n\t\r]+return\s"(\w+)"/m', $java, $matches))
    {
        $replacements['%name%'] = $matches[1];
    }

    $filename = @$replacements['%name%'];
    if(empty($filename) || substr($filename, 0, 1) == "_")
    {
        continue;
    }


    print "Processing: {$filename}\n";

    /*
    if(!(preg_match('/extends\sVariationFunc/', $java) || preg_match('/extends\sSimpleVariationFunc/', $java)))
    {
        print "--not a variation function, skipping\n";
        continue;
    }
    */

    // collect all the private variables
    $params = array();
    foreach($lines as $line)
    {

        // I have no idea why I couldn't make "private" an optional group/word here
        if(preg_match('/^\s\sprivate\s(\bdouble\b|\bboolean\b|\bint\b)\s/', $line, $matches) ||
            preg_match('/^\s\sprivate final\s(\bdouble\b|\bboolean\b|\bint\b)\s/', $line, $matches) ||
            preg_match('/^\s\sprotected\s(\bdouble\b|\bboolean\b|\bint\b)\s/', $line, $matches) ||
            preg_match('/^\s\s(\bdouble\b|\bboolean\b|\bint\b)\s/', $line, $matches) ||
            preg_match('/^\s\sprivate\sdouble\[\]\s/', $line, $matches) ||
            preg_match('/^\s\sdouble\[\]\s/', $line, $matches) ||
            preg_match('/^\s\sprivate\s(List<\w+>)\s/', $line, $matches)
    )
        {
            $line = trim($line);

            $parts = explode(';', $line);
            $line = $parts[0];
            $comment = @$parts[1];

            // looks like a function! 
            if (strpos($line, '{') !== false && strpos($line, '(') !== false && strpos($line, ')') !== false)
            {
                continue;
            }

            $line = str_replace('private ', '', $line);
            $line = str_replace('protected ', '', $line);
            $line = str_replace('final ', '', $line);
            $line = str_replace(';', '', $line);

            $parts = explode(' ', $line);
            $type = array_shift($parts);

            // don't split if in-line struct define
            if (strpos($line, '{') !== false)
            {
                $parts = [join(' ', $parts)];
            }
            else
            {
                $parts = explode(', ', join(' ', $parts));
            }

            foreach($parts as $def)
            {
                $pair = explode(' = ', $def);
                $params[] = [ "type" => $type, "code" => $pair[0], "default" => @$pair[1], "comment" => $comment ];
            }
        }

        // some hardcoded point stuff
        if(preg_match('/^\s\sprivate\sPoint\s(\w+)\s/', $line, $matches))
        {

            $params[] = ["type" => "Point", "code" => $matches[1], "default" => "POINT(0,0,0)", "comment" => "// converted"];
        }

    }

    // get all int consts
    $consts = array();
    if(preg_match_all('/^\s\sprivate\sstatic\sfinal\sint\s(\w+)\s=\s(\d+);/smx', $java, $matches, PREG_SET_ORDER))
    {
        foreach($matches as $match)
        {
            $consts[] = "const int {$match[1]} = {$match[2]};";
        }
    }

    if(preg_match_all('/^\s\sprivate\sstatic\sint\s(\w+)\s=\s(\d+);/smx', $java, $matches, PREG_SET_ORDER))
    {
        foreach($matches as $match)
        {
            $consts[] = "const int {$match[1]} = {$match[2]};";
        }
    }

    // get all double consts
    if(preg_match_all('/^\s\sprivate\sstatic\sfinal\sdouble\s(\w+)\s=\s([\d\.]+);/smx', $java, $matches, PREG_SET_ORDER))
    {
        foreach($matches as $match)
        {
            $consts[] = "const double {$match[1]} = {$match[2]};";
        }
    }

    // bros, lint your code
    if(preg_match_all('/^\s\sprivate\sfinal\sstatic\sdouble\s(\w+)\s=\s([\d\.]+);/smx', $java, $matches, PREG_SET_ORDER))
    {
        foreach($matches as $match)
        {
            $consts[] = "const double {$match[1]} = {$match[2]};";
        }
    }


    $replacements['%consts%'] = join("\n", $consts);

    $names = array();
    // get all the name constants
    if(preg_match_all('/[\bpublic\b|\bprivate\b]\sstatic\sfinal\sString\s(PARAM_\w+)\s=\s"(\w+)"/m', $java, $matches, PREG_SET_ORDER))
    {
        foreach($matches as $match)
        {
            $names[$match[1]] = $match[2];
        }
    }

    // and then add them in to the actual variables
    if(preg_match_all('/\((PARAM_\w+).equalsIgnoreCase\(pName\)\)\s{?\s+(\w+)\s=/msx', $java, $matches, PREG_SET_ORDER))
    {
        foreach($matches as $match)
        {
            $name = @$names[$match[1]];

            foreach($params as &$param)
            {
                if($param['code'] == $match[2])
                {
                    $param['name'] = $name;
                }
            }
        }
    }

    // determine which names to use for our variables
    $used_names = array();
    foreach($params as &$param)
    {
        if(empty($param['name']))
        {
            $param['id'] = $param['code'];

            // if we're a non-exposed variable, prefix with "_" if not already
            // I added this because some things collided with macros, but it's probably more clear in general
            if(substr($param['id'], 0, 1) != "_")
            {
                $param['id'] = "_" . $param['id'];
            }
        }
        else
        {
            $param['id'] = $param['name'];
        }

        $param['id'] = str_replace(['[', ']'], '', $param['id']);


        if(preg_match('/List<(\w+)>/', $param['type'], $matches))
        {
            $headersNeedVectors = true;
            $type = strtolower($matches[1]);
            $param['type'] = "vector <{$type}>";
            $param['default'] = "";
        }


        if(@$used_names[$param['id']])
        {
            $param['id'] = "_" . $param['id'];
        }

        $used_names[$param['id']] = 1;

        $search = array();
        $replace = array();

        $search[] = "/Math\.Pi/";
        $replace[] = "M_PI";

        $search[] = "/Math\.E/";
        $replace[] = "M_E";

        $search[] = "/Math.random\(\)/";
        $replace = "random01()";

        $param['default'] = preg_replace($search, $replace, $param['default']);
    }


    // send all private variables to struct
    $initialize = '';
    $struct = '';
    foreach($params as $p)
    {
        if($p['type'] == 'boolean')
        {
            $p['type'] = 'bool';
        }

        $id = $p['id'];

        // known size
        if(preg_match("/\[(\d+)\]/", $p['default'], $match))
        {
            $id .= "[{$match[1]}]";
            $p['default'] = '';
        }

        // unknown size
        if(preg_match("/\[\]/", $p['type'], $match))
        {
            $p['type'] = str_replace(['[', ']'], '', $p['type']);
            $size = count(explode(',', $p['default']));

            if(!preg_match("/[\[\]]/", $id))
            {
                $id .= "[{$size}]";
            }
            
            $p['default'] = '';
        }

        // empty defaults on functions--defaults aren't even used here, just more clear
        if(preg_match("/\(/", $p['default'], $match))
        {   
            $p['comment'] = ' // ' . $p['default'];
            $p['default'] = "";
        }

        // empty out defaults for non-number integers
         if($p['type'] == "int" && preg_match("/\D/", $p['default'], $match))
        {   
            $p['comment'] = ' // ' . $p['default'];
            $p['default'] = "0";
        }

        // empty out defaults for non-number doubles
         if($p['type'] == "double" && preg_match("/[^\d\.]/", $p['default'], $match))
        {   
            $p['comment'] = ' // ' . $p['default'];
            $p['default'] = "0.0";
        }

        $struct .= "\t{$p['type']} {$id}";


        if(!empty($p['default']) && empty($p['name']))
        {
            $d = $p['default'];

            $d = str_replace("random01()", "1.0", $d);

            $struct .= " = {$d}";

             $initialize .= "   VAR({$p['id']}) = {$p['default']};\n";
        }

        $struct .= ";{$p['comment']}\n";
    }

    $replacements['%struct%'] = $struct;

    // alright, time to build up the variables
    $variables = "";
    $prepare = "";
    foreach($params as $p)
    {
        // sadly don't support functions in defaults due to c header linking madness
        if(preg_match('/\w+\(\)/', $p['default']))
        {
            $p['default'] = "";
        }

        if(empty($p['default']))
        {
            if($p['type'] == 'double')
            {
                $p['default'] = 0.0;
            }

            if($p['type'] == 'int')
            {
                $p['default'] = 0;
            }

            if($p['type'] == 'boolean')
            {
                $p['default'] = FALSE;
            }
        }

        // bind to a variable in apo
        if(!empty($p['name']))
        {
            if($p['type'] == 'double')
            {
                $variables .= "\tVAR_REAL({$p['id']}, {$p['default']}),\n";
            }

            if($p['type'] == 'int')
            {
                $variables .= "\tVAR_INTEGER({$p['id']}, {$p['default']}),\n";
            }

            if($p['type'] == 'boolean')
            {
                $d = $p['default'] ? "1" : "0";

                $variables .= "\tVAR_INTEGER({$p['id']}, {$d}),\n";
            }
        }

        // if not a bound variable, and not a normal default, let's set to a default
        if(empty($p['name']) && !($p['default'] == "0.0" || $p['default'] != "0" || $p['default'] != "FALSE"))
        {
            $prepare .= "\tVVAR({$p['id']}) = {$p['default']};\n";
        }
    }

    // eat the last comma, whoops
    $variables = substr($variables, 0, -2) . "\n";

     // find all of our functions
    $function_names = array();
    if(preg_match_all('/^\s\s(?:private\s)?(?:public\s)?(\bvoid\b|\bdouble\b|\bint\b|\bboolean\b)\s(\w+)\((.*)\)\s{(.*)\s\s}/msU', $java, $matches, PREG_SET_ORDER))
    {
        foreach($matches as $match)
        {
            $function_names[] = $match[2];
        }
    }

    // port init code like a crazy person
    $init = $initialize . $init;
    $init = str_replace("    super.init(pContext, pLayer, pXForm, pAmount);\n", '', $init);
   
    // global replacements--this ends up being called on init/transform, but also function blogs
    // and yeah, at this point lots of stuff could be simplified/merged
    // I did things one-at-a-time so I could see which problems where there (and not introduce new ones)
    $search = array();
    $replace = array();

    $search[] = "/^(\s+)final\s/msU";
    $replace[] = '\1';

    $search[] = "/pAmount/";
    $replace[] = "VVAR";

    $search[] = "/pVarTP\.([xyz])/";
    $replace[] = 'FP\1';

    $search[] = "/pAffineTP\.([xyz])/";
    $replace[] = 'FT\1';

    $search[] = "/pVarTP\.color/";
    $replace[] = "TC";

    $search[] = "/pAffineTP\.color/";
    $replace[] = "TC";


    $search[] = "/\w+\.randomize\((\w*)\);/";
    $replace[] = 'GOODRAND_SEED(\1);';

    $search[] = "/\w+\.setSeed\(seed\)/";
    $replace[] = "GOODRAND_SEED(seed)";

    $search[] = "/\w+\s=\snew\sRandom\(seed\);/";
    $replace[] = "GOODRAND_SEED(seed);";

    $search[] = "/randGen\.randomize\(seed\);/";
    $replace[] = "GOODRAND_SEED(seed);";

    // these are getting specific--should find some way to generalize
    $search[] = "/(\s+)\w+\s=\snew\sRandom\((\(long\)\s)?(\w+)\);/";
    $replace[] = '\1GOODRAND_SEED(\3);';


    $search[] = "/Math\.random\(\)/";
    $replace[] = "GOODRAND_01()";

    $search[] = "/pContext\.random\(\)/";
    $replace[] = "GOODRAND_01()";

    $search[] = "/pContext\.random\(([^\)])/";
    $replace[] = 'GOODRAND_0X(\1';

    $search[] = "/\w*\.random\(\)/";
    $replace[] = "GOODRAND_01()";

    $search[] = "/\w+\.nextDouble\(\)/";
    $replace[] = "GOODRAND_01()";

    $search[] = "/(\w+)\s=\snew\sMarsagliaRandomGenerator\(\);/";
    $replace[] = '';

    $search[] = "/randGen\.random\(\)/";
    $replace[] = 'GOODRAND_01()';

    $search[] = "/\brand\.nextInt\b(\(((?:[^\(\)]++|(?1))*)\))/";
    $replace[] = 'GOODRAND_0X(\2)';


    $search[] = "/boolean\s/";
    $replace[] = "bool ";

    $search[] = "/Math\.cos/";
    $replace[] = "cos";

    $search[] = "/Math\.sin/";
    $replace[] = "sin";

    $search[] = "/Math\.acos/";
    $replace[] = "acos";

    $search[] = "/MathLib\.cos/";
    $replace[] = "cos";

    $search[] = "/MathLib\.sin/";
    $replace[] = "sin";

    $search[] = "/MathLib\.exp/";
    $replace[] = "exp";

    $search[] = "/Math\.pow/";
    $replace[] = "pow";

    $search[] = "/MathLib\.pow/";
    $replace[] = "pow";

    $search[] = "/Math\.abs/";
    $replace[] = "abs";

    $search[] = "/Math\.toRadians/";
    $replace[] = "DEGTORAD";

    $search[] = "/Math\.toDegrees/";
    $replace[] = "RADTODEG";

    $search[] = "/Math\.trunc/";
    $replace[] = "trunc";

    $search[] = "/Math\.sqrt/";
    $replace[] = "sqrt";

    $search[] = "/Math\.log/";
    $replace[] = "log";

    $search[] = "/Math\.copysign/";
    $replace[] = "copysign";

    $search[] = "/Math\.floor/";
    $replace[] = "floor";

    $search[] = "/Math\.round/";
    $replace[] = "round";

    $search[] = "/MathLib\.sqrt/";
    $replace[] = "sqrt";

    $search[] = "/MathLib\.atan2/";
    $replace[] = "atan2";

    $search[] = "/MathLib\.M_2PI/";
    $replace[] = "M_2PI";

    $search[] = "/MathLib\.M_PI/";
    $replace[] = "M_PI";

    $search[] = "/Math\.P[iI]/";
    $replace[] = "M_PI";

    $search[] = "/Math\.E/";
    $replace[] = "M_E";

    $search[] = "/Integer\.MAX_VALUE/";
    $replace[] = "INT_MAX";

    $search[] = "/Math\.min/";
    $replace[] = "MIN";

    $search[] = "/Math\.max/";
    $replace[] = "MAX";

    $search[] = "/Math\.rint/";
    $replace[] = "rint";

    $search[] = "/\smin\(/";
    $replace[] = " MIN(";

    $search[] = "/\max\(/";
    $replace[] = " MAX(";

    $search[] = "/MathLib\.fmod/";
    $replace[] = "fmod"; 

    $search[] = "/\ssign\(/";
    $replace[] = " SGN("; 

    $search[] = "/MathLib\.floor/";
    $replace[] = "floor";

    $search[] = "/MathLib\.fabs/";
    $replace[] = "fabs";

    $search[] = "/MathLib\.EPSILON/";
    $replace[] = "EPSILON";

    $search[] = "/Tools\.FTOI/";
    $replace[] = "";

    $search[] = "/cern\.jet\.math\.Bessel\.j1\(/";
    $replace[] = "_j1(";

    $search[] = "/sinAndCos\(([^,]*),\s(\w+),\s(\w+)\)/";
    $replace[] = 'fsincos(\1, &\2, &\3)';

    $search[] = "/pContext\.isPreserveZCoordinate\(\)/";
    $replace[] = "true /* pContext\.isPreserveZCoordinate() */";

    $search[] = "/pVarTP\.doHide\s=\strue;/";
    $replace[] = "/* pVarTP.doHide = true; */";

    $search[] = "/pVarTP\.doHide\s=\sfalse;/";
    $replace[] = "/* pVarTP.doHide = false; */";

    $search[] = "/pAffineTP\.doHide\s=\strue;/";
    $replace[] = "/* pAffineTP.doHide = true; */";

    $search[] = "/pAffineTP\.doHide\s=\sfalse;/";
    $replace[] = "/* pAffineTP.doHide = false; */";

    $search[] = "/pAffineTP\.getPrecalcAtan\(\)/";
    $replace[] = "atan2(FTx, FTy)";

    $search[] = "/pAffineTP\.getPrecalcAtanYX\(\)/";
    $replace[] = "atan2(FTx, FTy)";

    $search[] = "/pAffineTP\.getPrecalcSqrt\(\)/";
    $replace[] = "(sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON)";

    $search[] = "/pAffineTP\.getPrecalcSinA\(\)/";
    $replace[] = "(FTx / (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON))";

    $search[] = "/pAffineTP\.getPrecalcCosA\(\)/";
    $replace[] = "(FTy / (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON))";

    $search[] = "/pAffineTP\.getPrecalcSumsq\(\)/";
    $replace[] = "(FTx * FTx + FTy * FTy)";

    $search[] = "/XYZPoint\s(\w*)\s=\snew\sXYZPoint\(\);/";
    $replace[] = 'Point \1 = POINT(0,0,0);';

    $search[] = "/(\w*\.invalidate\(\);)/";
    $replace[] = '/* \1 */';

    $search[] = "/(\w*)\.getPrecalcSqrt\(\)/";
    $replace[] = 'POINT_SQTR(\1)';

    $search[] = "/pContext\.random/";
    $replace[] = "rand0x";

    $search[] = "/FastMath\.hypot/";
    $replace[] = "hypot";

    $search[] = "/pXForm.getXYCoeff(\d\d)\(\)/";
    $replace[] = 'XFORM_COEFF_\1';

    $search[] = "/(\w+)\[\]\s=\snew\sdouble\[(\d+)\]([,;])/";
    $replace[] = '\1[\2]\3';

     // redo function params so it always passes our "vp" reference
    foreach($function_names as $func)
    {
        $search[] = "/({$func})\(/";
        $replace[] = '\1(vp, ';;
    }

    // some corner cases
    $search[] = "/\(pContext([,)])/";
    $replace[] = '(vp\1';

    $search[] = "/, pContext\)/";
    $replace[] = ')';

    // strip [] from code before later substitutions
    foreach($params as &$param)
    {
        $param['code'] = str_replace(['[', ']'], '', $param['code']);
    }

    // actually do these big replacements
    $init = preg_replace($search, $replace, $init);
    $transform = preg_replace($search, $replace, $transform);

    // save for later
    $search_static = $search;
    $replace_static = $replace;

    // replace the named variables (hey look, a re-usable function!)
    $init = ReplaceWithVar($init);
    $transform = ReplaceWithVar($transform);

    // old variation code had some this.whatever references
    $init = str_replace("this.VAR", "VAR", $init);
    $transform = str_replace("this.VAR", "VAR", $transform);

    // early outs
    $init = str_replace("return;", "return TRUE;", $init);
    $transform = str_replace("return;", "return TRUE;", $transform);

    // one-liner empty java syntax, just going to fix here
    $transform = str_replace('transform(pContext, pXForm, pAffineTP, pVarTP, VVAR, FTx, FTy);', '', $transform);   

    $functions = "";
    if(preg_match_all('/^\s\s(?:private\s)?(?:public\s)?(\bvoid\b|\bdouble\b|\bint\b|\bboolean\b)\s(\w+)\((.*)\)\s{(.*)\n\s\s}/msU', $java, $matches, PREG_SET_ORDER))
    {
        foreach($matches as $match)
        {
            if(in_array($match[2], ["init", "transform", "setParameter", "getPriority"]))
            {
                continue;
            }

            $block = preg_replace($search_static, $replace_static, $match[4]);
            $block = ReplaceWithVar($block);

            $block = str_replace("this.VAR", "VAR", $block);
            $block = str_replace("this.VAR", "VAR", $block);

            $args = $match[3];
            $args = str_replace('FlameTransformationContext pContext, ', '', $args);
            $args = str_replace('FlameTransformationContext pContext', '', $args);

            $args = trim($args);
            if(!empty($args))
            {
                $args = ", {$args}";
            }

            $function = <<<DONE

{$match[1]} {$match[2]} (Variation* vp{$args}) {
{$block}
}

DONE;
            
            $functions .= $function;
        }
    }

    if($headersNeedVectors)
    {
        $headers .= "#include <vector>\nusing namespace std;\n";
    }

    $replacements['%variables%'] = $variables;
    $replacements['%prepare%'] = $prepare . $init;
    $replacements['%calc%'] = $transform;
    $replacements['%functions%'] = $functions;
    $replacements['%headers%'] = $headers;

    // these things ended up breaking, and rather than figure out the root cause, I just fixed afterwards
    // not a long-term move, but hey, here we are

    $replacements[', XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount)'] = ')';
    $replacements[', pXForm, pAffineTP, pVarTP, VVAR)'] = ')';

    $replacements[', XYZPoint pAffineTP, XYZPoint pVarTP,'] = '';
    $replacements[', pAffineTP, pAffineTP'] = '';
    $replacements[', vp, pAffineTP, pAffineTP'] = '';
    $replacements['(vp, pContext)'] = '(vp)';
    $replacements['(vp, pContext,'] = '(vp,';
    $replacements['(vp, )'] = '(vp)';

    // use our template
    $template = file_get_contents("templates/base.cpp");
    $search = array();
    $replace = array();
    foreach($replacements as $s => $r)
    {
        $search[] = $s;
        $replace[] = $r;
    }

    $template = str_replace($search, $replace, $template);

    // try to fix all broken suffixes -- some files had "1.d", "1.0d", etc
    $template = preg_replace('/([^0-9])(\d+)\.d?([^a-zA-Z0-9_])/', '\1\2.0\3', $template);
    $template = preg_replace('/([^0-9])(\d+\.\d*)d([^a-zA-Z0-9_])/', '\1\2\3', $template);

    // paste in original java for easier reference
    $template .= "\n\n\n// original java file embedded here:\n//\n";
    foreach($original as $line)
    {
        $template .= "// {$line}\n";
    }

    file_put_contents('output/' . $filename . '.cpp', $template);

    // save out empty stub plugin in case of compile failures
    $template = file_get_contents("templates/stub.cpp");
    $search = array();
    $replace = array();
    foreach($replacements as $s => $r)
    {
        $search[] = $s;
        $replace[] = $r;
    }

    $template = str_replace($search, $replace, $template);

    // try to fix all broken suffixes -- some files had "1.d", "1.0d", etc
    $template = preg_replace('/([^0-9])(\d+)\.d?([^a-zA-Z0-9_])/', '\1\2.0\3', $template);
    $template = preg_replace('/([^0-9])(\d+\.\d*)d([^a-zA-Z0-9_])/', '\1\2\3', $template);

    // paste in original java for easier reference
    $template .= "\n\n\n// original java file embedded here:\n//\n";
    foreach($original as $line)
    {
        $template .= "// {$line}\n";
    }

    file_put_contents('stubs/' . $filename . '.cpp', $template);
}

function ReplaceWithVar($text)
{
    global $params;

    // wrap previously-private variables in VAR
    foreach($params as $p)
    {
        // do any vector replacement
        if(preg_match("/vector/", $p['type']))
        {
            $text = preg_replace("/({$p['code']})\.add\(/", '\1.emplace_back(', $text);
            $text = preg_replace("/({$p['code']})\.get\(/", '\1.at(', $text);
        }
        
        $text = preg_replace_callback("/(.{0,2}\W)\Q{$p['code']}\E([^a-zA-Z0-9_])/", function ($matches) use ($p) {

            // don't nest, i.e. one parameter is "d" and the other is "p_d"
            if($matches[1] == "AR(")
                return $matches[0];

            // might be pow, whoops--not sure what other things are likely overlapping function names
            if(in_array($p['code'], ["pow", "log"]) && $matches[2] == "(")
                return $matches[0];

            return "{$matches[1]}VAR({$p['id']}){$matches[2]}";
        }, $text);
        

        $text = preg_replace("/VAR\((\w+)\)\.value/", 'VAR(\1)', $text);       
    }

    return $text;

}